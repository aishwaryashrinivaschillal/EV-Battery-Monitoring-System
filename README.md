# 🔋 EV Battery Monitoring System

## 📌 Project Overview

The **EV Battery Monitoring System** is an Arduino Uno based prototype designed to monitor important electrical and thermal parameters of an electric vehicle (EV) battery.

The system measures **battery voltage, current, power, and temperature** using appropriate sensors. The measured parameters are processed by the Arduino Uno and displayed on a **16×2 I2C LCD** and through the Serial Monitor.

The project also includes a **Battery Management System (BMS)** for battery protection and a regulated power-supply section for providing suitable voltage levels to the control circuitry.

A rule-based battery aging-risk assessment is implemented using temperature and current conditions. The system is also designed to support automatic cooling-fan activation through a relay when the temperature exceeds a predefined threshold.

---

## 🎯 Objectives

The main objectives of this project are:

- To monitor the voltage of an EV battery.
- To measure the current drawn from the battery.
- To calculate the electrical power using measured voltage and current.
- To monitor battery temperature using an NTC thermistor.
- To display real-time battery parameters on a 16×2 LCD.
- To provide battery status information through the Serial Monitor.
- To estimate battery aging risk using temperature and current conditions.
- To integrate a Battery Management System (BMS) for battery protection.
- To provide a regulated power supply for the control circuitry.
- To implement temperature-based cooling control using a relay and cooling fan.

---

# 📚 Theory

## 🔋 1. EV Battery Monitoring

The battery is one of the most important components of an electric vehicle. Its electrical and thermal conditions directly affect vehicle performance, efficiency, reliability, and safety.

Continuous monitoring of parameters such as:

- Voltage
- Current
- Power
- Temperature

helps identify abnormal operating conditions and provides useful information about battery performance.

---

## ⚡ 2. Voltage Monitoring

Battery voltage is measured using a voltage sensor connected to the analog input of the Arduino Uno.

The Arduino's ADC converts the sensor output voltage into a digital value.

For a scaled voltage sensor:

**Battery Voltage = Sensor Voltage × Scaling Factor**

In this project, the measured voltage is processed by the Arduino and displayed on the LCD and Serial Monitor.

---

## 🔌 3. Current Monitoring

Current is measured using the **HW-872B current sensor**.

The sensor produces an analog voltage corresponding to the current flowing through the circuit.

The Arduino reads this analog voltage and converts it into current using the sensor sensitivity.

For the selected sensor:

**Current = (Sensor Voltage − Zero Current Voltage) / Sensor Sensitivity**

The current value is then used for power calculation and battery aging-risk assessment.

---

## ⚡ 4. Power Calculation

Electrical power is calculated from the measured voltage and current.

**P = V × I**

Where:

- P = Power in watts (W)
- V = Voltage in volts (V)
- I = Current in amperes (A)

The calculated power provides an indication of the electrical load and energy transfer conditions of the battery system.

---

## 🌡️ 5. Temperature Monitoring

Battery temperature is monitored using a **10 kΩ NTC thermistor**.

An NTC thermistor has a negative temperature coefficient, meaning its resistance decreases as temperature increases.

The thermistor is connected as part of a voltage-divider circuit. The Arduino measures the resulting analog voltage and calculates the thermistor resistance.

The temperature is then estimated using the Beta equation.

Temperature monitoring is important because excessive battery temperature can affect battery performance, lifetime, and safety.

---

## 🛡️ 6. Battery Management System (BMS)

A **Battery Management System (BMS)** is used with the battery pack to provide battery monitoring and protection functions.

The BMS forms an important safety layer for the battery pack and can help manage abnormal operating conditions such as over-voltage, under-voltage, over-current, and temperature-related conditions depending on the specific BMS module used.

In this project, the BMS is integrated with the battery pack as part of the overall monitoring and protection system.

---

## 🔋 7. Battery Pack

The prototype uses **18650 lithium-ion cells** as the battery source.

Lithium-ion batteries are widely used in electric mobility applications because of their high energy density and rechargeable characteristics.

The battery pack is connected to the BMS and monitoring circuitry.

---

## 🔥 8. Heat-Stress Indicator

The project uses an I²-based heat-stress indicator:

**Heat Stress = I²**

This provides an additional indication of the effect of increasing current on electrical heating.

Since heating losses in resistive elements are related to I²R, an increase in current can significantly increase thermal stress.

---

## 🧠 9. Battery Aging-Risk Assessment

The system uses a **rule-based battery aging-risk assessment**.

The risk level is classified as:

| Condition | Aging Risk |
|---|---|
| High temperature + high current | HIGH |
| Moderate temperature/current or high heat-stress index | MEDIUM |
| Normal operating conditions | LOW |

The Arduino evaluates the measured temperature and current and assigns the corresponding risk level.

> **Note:** The current implementation is threshold-based rule logic rather than a mathematical fuzzy-logic controller.

---

# 🧩 Components Used

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| 18650 Li-ion Battery Cells | Battery source |
| BMS Module | Battery management and protection |
| Voltage Sensor | Voltage measurement |
| HW-872B Current Sensor | Current measurement |
| 10 kΩ NTC Thermistor | Temperature measurement |
| 16×2 I2C LCD | Display of measured parameters |
| Relay Module | Switching the cooling fan |
| Cooling Fan | Intended thermal management |
| 12 V to 5 V/3.3 V Regulator Circuit | Power regulation |
| Breadboard | Circuit prototyping |
| Jumper Wires | Electrical connections |

---

# 🔌 Circuit Connections

## Arduino Connections

| Component | Arduino Connection |
|---|---|
| Voltage Sensor Output | A0 |
| Current Sensor Output | A1 |
| NTC Thermistor Output | A3 |
| Relay Input | D7 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| LCD VCC | 5V |
| LCD GND | GND |

> The exact power and sensor connections should be verified against the actual hardware circuit before final documentation.

---

# 🔋 Power Supply Section

The prototype includes a regulated power-supply section.

The battery-side supply is approximately **12 V DC**, which is regulated to suitable lower voltage levels such as **5 V and 3.3 V** for the control and sensor circuitry.

The regulation stage helps provide appropriate supply voltages to the Arduino and other electronic components.

### Power Flow

```text
12 V DC Battery Supply
          ↓
Power Regulation Circuit
          ↓
   ┌──────┴──────┐
   ↓             ↓
  5 V          3.3 V
   ↓             ↓
Arduino       Sensors /
LCD           Modules

# ⚙️ Working Principle

The EV Battery Monitoring System continuously monitors the electrical and thermal parameters of the battery using sensors connected to an Arduino Uno.

1. The 18650 lithium-ion battery pack provides the electrical supply.
2. The BMS is connected to the battery pack to provide battery management and protection.
3. The 12 V DC supply is regulated to suitable voltage levels such as 5 V and 3.3 V for the electronic circuitry.
4. The voltage sensor measures the battery voltage and sends an analog signal to the Arduino.
5. The HW-872B current sensor measures the current flowing through the system.
6. The NTC thermistor senses the battery/system temperature.
7. The Arduino Uno processes the sensor readings.
8. Electrical power is calculated using the measured voltage and current.
9. An I²-based heat-stress indicator is calculated from the measured current.
10. The temperature and current values are evaluated using predefined rules to determine the battery aging-risk level as LOW, MEDIUM, or HIGH.
11. The measured voltage, current, temperature, power, aging risk, and fan status are displayed on the 16×2 LCD.
12. The same information is transmitted to the Serial Monitor for observation and analysis.
13. When the temperature reaches the defined threshold, the Arduino is designed to activate the relay and turn ON the cooling fan.
14. When the temperature falls below the lower threshold, the relay is switched OFF and the fan is turned OFF.
15. The process continuously repeats to provide real-time battery monitoring.
16. The Arduino is designed to activate the relay and cooling fan when the temperature reaches the predefined threshold.

# 🔄 System Flow

The overall working flow of the EV Battery Monitoring System is shown below:

```text
                 START
                   ↓
       Initialize Arduino Uno
                   ↓
        Initialize LCD & Serial
                   ↓
          Read Voltage Sensor
                   ↓
          Read Current Sensor
                   ↓
        Read Temperature Sensor
                   ↓
          Calculate Power
            P = V × I
                   ↓
       Calculate Heat Stress
               I² Index
                   ↓
        Determine Aging Risk
          LOW / MEDIUM / HIGH
                   ↓
        Check Temperature
                   ↓
          ┌────────┴────────┐
          ↓                 ↓
   Temperature High   Temperature Normal
          ↓                 ↓
      Relay ON          Relay OFF
          ↓                 ↓
       Fan ON            Fan OFF
          └────────┬────────┘
                   ↓
          Display Parameters
              on LCD
                   ↓
        Send Data to Serial
             Monitor
                   ↓
                 REPEAT

                 # 💻 Software Implementation

The system is programmed using the Arduino IDE. The Arduino Uno reads the analog signals from the voltage sensor, current sensor, and NTC thermistor and processes the measured values.

The software performs the following operations:

- Reads battery voltage through analog pin A0.
- Reads current through the HW-872B current sensor connected to A1.
- Reads temperature through the NTC thermistor connected to A3.
- Calculates electrical power using:

  **P = V × I**

- Calculates an I²-based heat-stress indicator.
- Determines the battery aging-risk level as LOW, MEDIUM, or HIGH using predefined threshold conditions.
- Displays the measured parameters on the 16×2 I2C LCD.
- Sends the monitoring data to the Serial Monitor at 9600 baud.
- Controls the relay according to the predefined temperature threshold for the intended cooling-fan operation.

The complete Arduino source code is available in:

```text
Arduino_Code/EV_Battery_Monitoring.ino

# 📟 LCD Display

A 16×2 I2C LCD is used to display the battery monitoring parameters in real time.

The LCD alternates between two screens.

### Screen 1 — Battery Parameters

```text
V:12.0 I:2.5
T:32.5 P:30

# 🖥️ Serial Monitor

The Arduino Uno also sends the measured battery parameters to the Serial Monitor through serial communication at a baud rate of **9600**.

The Serial Monitor provides the following information:

- Battery voltage
- Battery current
- Temperature
- Calculated power
- Heat-stress index
- Battery aging-risk level
- Cooling-fan status

### Example Serial Monitor Output

```text
--------------------------------
Voltage      : 12.00 V
Current      : 2.50 A
Temperature  : 32.50 C
Power        : 30.00 W
Heat Stress  : 6.25
Aging Risk   : LOW
Cooling Fan  : OFF
--------------------------------

# 📸 Hardware Setup

The prototype hardware consists of the Arduino Uno, 18650 lithium-ion battery cells, BMS module, voltage sensor, current sensor, NTC thermistor, 16×2 I2C LCD, relay module, cooling fan, breadboard, and power-regulation circuitry.

The components are interconnected to enable real-time monitoring of the battery's electrical and thermal parameters.

### Prototype Hardware

![EV Battery Monitoring System - Hardware Setup](Project_Photos/hardware_setup.jpg)

**Figure 1: Prototype hardware setup of the EV Battery Monitoring System.**

# 📊 Results

The developed prototype is designed to monitor the following battery parameters in real time:

| Parameter | Measurement / Function |
|---|---|
| Voltage | Measures battery voltage |
| Current | Measures battery/load current |
| Power | Calculated using P = V × I |
| Temperature | Measured using NTC thermistor |
| Heat Stress | Calculated using I²-based indicator |
| Aging Risk | Classified as LOW, MEDIUM, or HIGH |
| Fan Status | Displays intended cooling-control status |

### Output Images

Actual experimental output screenshots and LCD readings will be added here after testing.

The `Output` folder is reserved for:

```text
Output/
├── lcd_output.png
├── serial_monitor.png
├── voltage_output.png
├── current_output.png
├── temperature_output.png
└── power_output.png

# ⚠️ Limitations

The current prototype has the following limitations:

- The cooling fan and relay operation could not be successfully demonstrated during prototype testing.
- Sensor calibration may be required to improve the accuracy of voltage, current, and temperature measurements.
- The accuracy of the measured values depends on the characteristics and calibration of the selected sensor modules.
- The battery aging-risk assessment is based on predefined threshold rules and does not represent a complete battery health prediction model.
- The current implementation uses rule-based logic rather than a true fuzzy-logic controller or machine-learning model.
- The prototype is developed for academic and experimental purposes and should not be considered a safety-critical EV Battery Management System.

# 🚀 Future Scope

The project can be further improved and extended in the following ways:

- Successfully integrate and test automatic cooling-fan control using the relay.
- Improve voltage, current, and temperature sensor calibration for better measurement accuracy.
- Add real-time data logging for long-term battery performance analysis.
- Implement IoT-based monitoring to access battery parameters remotely.
- Develop a mobile or web-based dashboard for real-time visualization.
- Implement State of Charge (SOC) estimation.
- Implement State of Health (SOH) estimation.
- Develop advanced battery aging and degradation prediction techniques.
- Implement a true fuzzy-logic-based battery aging assessment system.
- Explore machine-learning techniques for battery health and failure prediction.
- Improve thermal management using automatic temperature-based cooling.
- Integrate advanced BMS features for improved battery protection and monitoring.

# 🌍 Applications

The EV Battery Monitoring System can be used as a prototype for monitoring and analyzing battery conditions in various applications, including:

- 🚗 Electric vehicle battery monitoring
- 🛵 Electric scooters and two-wheelers
- 🔋 Battery energy storage systems
- ☀️ Solar energy storage systems
- ⚡ Portable battery-powered systems
- 🧪 Battery testing and research laboratories
- 🎓 Academic and educational battery-management projects
- 🔌 Electric mobility and charging systems

The monitoring approach can also be extended to larger battery packs by using appropriately rated sensors, protection circuits, and battery-management systems.

# 🏁 Conclusion

The **EV Battery Monitoring System** demonstrates an Arduino Uno based approach for monitoring important electrical and thermal parameters of an EV battery.

The prototype measures **voltage, current, and temperature**, calculates electrical power using the relationship **P = V × I**, and uses an I²-based heat-stress indicator to assess operating conditions.

A rule-based battery aging-risk assessment classifies the battery condition into **LOW, MEDIUM, or HIGH risk** based on temperature and current conditions. The monitored parameters are displayed on a 16×2 I2C LCD and transmitted through the Serial Monitor.

The integration of the **BMS, regulated power-supply circuit, sensors, LCD, and proposed relay-based cooling system** provides a foundation for developing a more advanced EV battery monitoring and thermal-management system.

Although the automatic cooling-fan operation requires further hardware troubleshooting, the project demonstrates the fundamental concepts involved in **battery parameter monitoring, thermal observation, power calculation, and battery-condition assessment**.

# 🛠️ Technologies Used

- **Microcontroller:** Arduino Uno
- **Programming Language:** Embedded C/C++
- **Development Environment:** Arduino IDE
- **Display:** 16×2 I2C LCD
- **Temperature Sensor:** NTC Thermistor
- **Voltage Measurement:** Voltage Sensor
- **Current Measurement:** HW-872B Current Sensor
- **Battery:** 18650 Lithium-ion Cells
- **Battery Protection:** BMS Module
- **Control:** Relay Module
- **Thermal Management:** Cooling Fan
- **Power Regulation:** 12 V DC to regulated 5 V / 3.3 V
- **Communication:** Serial Monitor / I2C

# 📁 Repository Structure

```text
EV-Battery-Monitoring-System/
│
├── Arduino_Code/
│   └── EV_Battery_Monitoring.ino
│
├── Circuit_Diagram/
│
├── Documentation/
│
├── Output/
│
├── Project_Photos/
│   └── hardware_setup.jpg
│
└── README.md