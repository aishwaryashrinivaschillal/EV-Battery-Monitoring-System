#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

// =====================================================
// LCD
// =====================================================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// =====================================================
// PIN DEFINITIONS
// =====================================================
#define VOLT_PIN   A0
#define CURR_PIN   A1
#define TEMP_PIN   A3

#define RELAY_PIN  7

// =====================================================
// VOLTAGE SENSOR
// Common 0-25V voltage sensor module
// Scaling factor = 5
// =====================================================
const float VOLTAGE_SCALE = 5.0;

// =====================================================
// CURRENT SENSOR - HW-872B
// Sensitivity = 66 mV/A
// =====================================================
const float CURRENT_SENSITIVITY = 0.066;
const float CURRENT_ZERO_VOLTAGE = 2.5;

// =====================================================
// NTC THERMISTOR
// 10k NTC, Beta = 3950
// =====================================================
const float R_FIXED = 10000.0;
const float R_NOMINAL = 10000.0;
const float BETA = 3950.0;
const float T0 = 298.15;       // 25°C in Kelvin

// =====================================================
// FAN / RELAY TEMPERATURE CONTROL
// =====================================================
const float FAN_ON_TEMP  = 45.0;
const float FAN_OFF_TEMP = 42.0;

// Most relay modules are ACTIVE LOW.
// If your relay is ACTIVE HIGH, change this to false.
// =====================================================
const bool RELAY_ACTIVE_LOW = true;

// =====================================================
// BATTERY AGING RISK THRESHOLDS
// =====================================================
const float HIGH_TEMP = 45.0;
const float MEDIUM_TEMP = 35.0;

const float HIGH_CURRENT = 12.0;
const float MEDIUM_CURRENT = 6.0;

// =====================================================
// VARIABLES
// =====================================================
float voltage = 0.0;
float current = 0.0;
float temperature = 0.0;
float power = 0.0;
float heatStress = 0.0;

String agingRisk;

bool fanState = false;

// =====================================================
// FUNCTION: Control Relay
// =====================================================
void setFan(bool state)
{
  fanState = state;

  if (RELAY_ACTIVE_LOW)
  {
    digitalWrite(RELAY_PIN, state ? LOW : HIGH);
  }
  else
  {
    digitalWrite(RELAY_PIN, state ? HIGH : LOW);
  }
}

// =====================================================
// FUNCTION: Read Voltage
// =====================================================
float readVoltage()
{
  int rawValue = analogRead(VOLT_PIN);

  float sensorVoltage = rawValue * (5.0 / 1023.0);

  float batteryVoltage = sensorVoltage * VOLTAGE_SCALE;

  return batteryVoltage;
}

// =====================================================
// FUNCTION: Read Current
// =====================================================
float readCurrent()
{
  int rawValue = analogRead(CURR_PIN);

  float sensorVoltage = rawValue * (5.0 / 1023.0);

  float measuredCurrent =
      (sensorVoltage - CURRENT_ZERO_VOLTAGE)
      / CURRENT_SENSITIVITY;

  return measuredCurrent;
}

// =====================================================
// FUNCTION: Read NTC Temperature
// =====================================================
float readTemperature()
{
  int rawValue = analogRead(TEMP_PIN);

  // Prevent division by zero
  if (rawValue <= 0)
  {
    return -999.0;
  }

  float voltageNTC = rawValue * (5.0 / 1023.0);

  // Prevent invalid calculation
  if (voltageNTC <= 0.01 || voltageNTC >= 4.99)
  {
    return -999.0;
  }

  // Voltage divider:
  // +5V --- R_FIXED --- ADC --- NTC --- GND
  float resistanceNTC =
      R_FIXED * voltageNTC / (5.0 - voltageNTC);

  // Beta equation
  float temperatureKelvin =
      1.0 /
      (
        (1.0 / T0) +
        (1.0 / BETA) *
        log(resistanceNTC / R_NOMINAL)
      );

  float temperatureCelsius =
      temperatureKelvin - 273.15;

  return temperatureCelsius;
}

// =====================================================
// FUNCTION: Determine Battery Aging Risk
// =====================================================
void calculateAgingRisk()
{
  heatStress = fabs(current) * fabs(current);

  // HIGH RISK
  if ((temperature >= HIGH_TEMP) &&
      (fabs(current) >= HIGH_CURRENT))
  {
    agingRisk = "HIGH";
  }

  // MEDIUM RISK
  else if ((temperature >= MEDIUM_TEMP &&
            fabs(current) >= MEDIUM_CURRENT) ||
           (heatStress >= 80.0))
  {
    agingRisk = "MEDIUM";
  }

  // LOW RISK
  else
  {
    agingRisk = "LOW";
  }
}

// =====================================================
// FUNCTION: Control Cooling Fan
// =====================================================
void controlCoolingFan()
{
  // Turn fan ON when temperature reaches 45°C
  if (!fanState && temperature >= FAN_ON_TEMP)
  {
    setFan(true);
  }

  // Turn fan OFF only after temperature falls below 42°C
  else if (fanState && temperature <= FAN_OFF_TEMP)
  {
    setFan(false);
  }
}

// =====================================================
// SETUP
// =====================================================
void setup()
{
  // Relay configuration
  pinMode(RELAY_PIN, OUTPUT);

  // Keep fan OFF during startup
  setFan(false);

  // LCD initialization
  lcd.init();
  lcd.backlight();

  // Serial communication
  Serial.begin(9600);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("EV Battery");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring");

  delay(2000);

  lcd.clear();
}

// =====================================================
// MAIN LOOP
// =====================================================
void loop()
{
  // ---------------------------------------------------
  // READ SENSORS
  // ---------------------------------------------------
  voltage = readVoltage();

  current = readCurrent();

  temperature = readTemperature();

  // ---------------------------------------------------
  // POWER CALCULATION
  // P = V x I
  // ---------------------------------------------------
  power = voltage * current;

  // ---------------------------------------------------
  // AGING RISK
  // ---------------------------------------------------
  calculateAgingRisk();

  // ---------------------------------------------------
  // FAN CONTROL
  // ---------------------------------------------------
  if (temperature > -100)
  {
    controlCoolingFan();
  }

  // ===================================================
  // LCD SCREEN 1
  // Voltage and Current
  // ===================================================
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(voltage, 1);

  lcd.print(" I:");
  lcd.print(current, 1);

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature, 1);

  lcd.print(" P:");
  lcd.print(power, 0);

  delay(1500);

  // ===================================================
  // LCD SCREEN 2
  // Aging Risk + Fan Status
  // ===================================================
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Risk:");
  lcd.print(agingRisk);

  lcd.setCursor(0, 1);

  if (fanState)
  {
    lcd.print("Fan:ON");
  }
  else
  {
    lcd.print("Fan:OFF");
  }

  delay(1500);

  // ===================================================
  // SERIAL MONITOR
  // ===================================================
  Serial.println("--------------------------------");

  Serial.print("Voltage      : ");
  Serial.print(voltage, 2);
  Serial.println(" V");

  Serial.print("Current      : ");
  Serial.print(current, 2);
  Serial.println(" A");

  Serial.print("Temperature  : ");
  Serial.print(temperature, 2);
  Serial.println(" C");

  Serial.print("Power        : ");
  Serial.print(power, 2);
  Serial.println(" W");

  Serial.print("Heat Stress  : ");
  Serial.println(heatStress, 2);

  Serial.print("Aging Risk   : ");
  Serial.println(agingRisk);

  Serial.print("Cooling Fan  : ");

  if (fanState)
  {
    Serial.println("ON");
  }
  else
  {
    Serial.println("OFF");
  }

  Serial.println("--------------------------------");

  delay(500);
}