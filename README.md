# Interfacing LM35 Temperature Sensor with Arduino UNO

![Interfacing LM35 Temperature Sensor with Arduino UNO](https://playwithcircuit.com/wp-content/uploads/2025/05/Interfacing-LM35-Temperature-Sensor-with-Arduino-UNO.webp)

The **LM35** is a simple and inexpensive analog temperature sensor that works particularly well with Arduino projects. It provides an analog voltage that changes linearly with temperature, so an Arduino can read the voltage through its ADC and convert it into a temperature value.

In this project, an **LM35 temperature sensor is interfaced with an Arduino UNO** to measure temperature in both Celsius and Fahrenheit. The measured temperature is displayed on a **16×2 I2C LCD**, while a common-cathode RGB LED provides a quick visual indication of the temperature level.

The complete project and additional Arduino tutorials are available on **[Play with Circuit](https://playwithcircuit.com/)**.

## Project Features

- Measure temperature using the LM35 analog temperature sensor
- Interface the LM35 directly with an Arduino UNO
- Display temperature in Celsius and Fahrenheit
- Show the readings on a 16×2 I2C LCD
- Use an RGB LED to indicate low, normal, and high temperature
- Read the LM35 output through Arduino's A0 analog input

## What is the LM35 Temperature Sensor?

The **LM35** is a precision analog temperature sensor whose output voltage is directly proportional to the temperature in degrees Celsius.

One of its main advantages is its simple linear output. The sensor has a sensitivity of approximately **10 mV/°C**, which makes temperature calculation straightforward when using the Arduino's analog-to-digital converter.

For example:

- At 0°C, the output is approximately 0 mV
- At 25°C, the output is approximately 250 mV
- At 100°C, the output is approximately 1.00 V

The LM35 can operate from **4 V to 30 V** and typically consumes only around **60 μA**, which helps keep self-heating low.

The sensor is also relatively easy to interface because it does not require external signal-conditioning circuitry for a basic Arduino temperature measurement application.

### LM35 Limitations

Although the LM35 is useful for many projects, it has a few limitations.

The sensor cannot directly measure negative temperatures in a basic single-supply configuration. A dual-polarity supply is required for applications that need to measure temperatures below 0°C. For projects where negative temperature measurement is required, a sensor such as the **TMP36** can be considered.

Since the LM35 provides an analog output, electrical noise can affect the readings, especially when the sensor is connected over longer wires or used in electrically noisy environments. A digital sensor such as the **DS18B20** can be a better choice when improved noise immunity is required.

## LM35 Specifications

The main specifications of the LM35 used in this project are:

- Operating voltage: **4 V to 30 V**
- Operating temperature range: **-55°C to 150°C**
- Typical current consumption: **60 μA**
- Output type: **Analog**
- Typical accuracy: **±0.5°C**
- Low impedance output: **0.1 Ω for 1 mA load**
- Linearity: **±0.25°C**
- Sensitivity: **10 mV/°C**

## How Does the LM35 Work?

Internally, the LM35 uses matched bipolar junction transistors and associated circuitry to generate a voltage that changes predictably with temperature.

Two transistors operate with different current densities. This creates a difference in their base-emitter voltages. The voltage difference is proportional to absolute temperature and can be expressed as:

```text
ΔVBE = VBE1 – VBE2 = (kT/q) × ln(I1/I2)
```

In the LM35 circuit, the transistor current ratio is designed to produce a predictable temperature-dependent voltage.

Here:

- **I1/I2 = 10**
- **T** is the absolute temperature in Kelvin
- **k** is Boltzmann's constant
- **q** is the electronic charge

The resulting temperature-dependent voltage is processed and scaled so that the sensor provides an output of approximately **10 mV for every 1°C**.

Therefore:

```text
0°C   → 0 mV
25°C  → 250 mV
100°C → 1.00 V
```

This simple relationship is what makes the LM35 convenient for microcontroller-based temperature measurement.

## LM35 Pinout

The LM35 has three pins:

![LM35 Temperature Sensor Pinout](https://playwithcircuit.com/wp-content/uploads/2025/05/LM35-Temperature-Sensor-Pinout.webp)

### Pin 1 – VCC

This is the power supply pin. The LM35 can operate from a supply voltage between **4 V and 30 V**.

### Pin 2 – OUT

This is the analog output pin. Its voltage changes according to the measured temperature at approximately **10 mV/°C**.

### Pin 3 – GND

Connect this pin to the ground of the Arduino or the common ground of the circuit.

## Measuring Temperature Using the LM35

The LM35 produces an output voltage that is proportional to temperature.

The basic relationship is:

```text
Vout = 10 mV/°C × T
```

Therefore, temperature can be calculated from the measured output voltage as:

```text
T = Vout × 100
```

where **Vout** is expressed in volts and **T** is the temperature in degrees Celsius.

For example, if the sensor output is **0.1 V**:

```text
Temperature = 0.1 × 100
            = 10°C
```

### Checking the LM35 with a Multimeter

The sensor output can also be checked using a multimeter.

Set the multimeter to **DC voltage mode**. Connect the negative probe to the LM35 ground pin and the positive probe to the sensor's output pin. Power the LM35 through its VCC pin.

At room temperature, around **25°C**, the output should be approximately **250 mV**.

This is a useful way to verify that the sensor is producing an expected output before connecting it to the Arduino.

## Components Required

The project requires the following hardware:

- Arduino UNO R3
- LM35 temperature sensor
- 220 Ω resistor
- Half-size breadboard
- Common-cathode RGB LED
- Jumper wires
- USB Type-A to Type-B cable
- 12 V power adapter
- 16×2 I2C LCD based on the PCF8574 I2C backpack

A **10 nF capacitor** is also used on the LM35 output to help stabilize the sensor reading.

## Software Requirements

Install the following software and library before building the project:

- **Arduino IDE 2.3.4 or later**
- **LiquidCrystal_I2C library by Frank de Brabander, version 1.1.2**

## Circuit Connections
![Wiring Diagram](https://playwithcircuit.com/wp-content/uploads/2025/05/Wiring-LM35-Temperature-Sensor-with-Arduino-UNO.webp)

The LM35 output is connected to the **A0 analog input** of the Arduino UNO. Its power pin is connected to the Arduino's **5 V** supply, and the ground pin is connected to Arduino GND.

The LM35 connections are:

```text
LM35          Arduino UNO
-------------------------
VCC    →      5V
OUT    →      A0
GND    →      GND
```

A **10 nF capacitor** is connected between the LM35 output and ground to help provide more stable readings.

The circuit is configured for measuring positive temperatures.

### RGB LED Connections

A common-cathode RGB LED is used to provide a visual indication of the temperature.

The LED connections are:

```text
RGB LED       Arduino UNO
-------------------------
Red           → Pin 10
Blue          → Pin 9
Green         → Pin 8
Cathode       → GND through 220 Ω resistor
```

The RGB LED changes color depending on the temperature level detected by the system:

- **Blue** – Low temperature
- **Green** – Normal temperature
- **Red** – High temperature

### I2C LCD Connections

The 16×2 LCD uses a **PCF8574-based I2C interface**. The I2C communication lines are connected to the Arduino UNO as follows:

```text
I2C LCD       Arduino UNO
-------------------------
SDA           → A4
SCL           → A5
VCC           → 5V
GND           → GND
```

On the Arduino UNO, **A4 is the SDA line and A5 is the SCL line**. Therefore, these pins should not be used for another analog-input function while the I2C LCD is being used.

## I2C LCD Address

The LCD uses the I2C address **0x27** in this project.

On a typical PCF8574 I2C LCD backpack, the **A0, A1, and A2 address jumpers should remain open/not shorted** for this address configuration.

When all three address jumpers are shorted, the address changes to **0x20**.

If the LCD does not display anything, checking the I2C address is one of the first things to verify.

## Complete Wiring Summary

The important connections for the complete project are:

```text
LM35
VCC  → Arduino 5V
OUT  → Arduino A0
GND  → Arduino GND

RGB LED
Red     → Arduino D10
Blue    → Arduino D9
Green   → Arduino D8
Cathode → GND through 220 Ω resistor

I2C LCD
SDA → Arduino A4
SCL → Arduino A5
VCC → Arduino 5V
GND → Arduino GND

LM35
10 nF capacitor → connected at the sensor output for stable readings
```

## How the Project Works

Once the circuit is powered, the LM35 continuously senses the surrounding temperature and produces a corresponding analog voltage.

The Arduino reads this voltage through its **A0 analog input**. Since the LM35 has a sensitivity of approximately **10 mV/°C**, the Arduino can convert the measured voltage into a Celsius temperature.

The Celsius value can then be converted into Fahrenheit using:

```text
°F = (°C × 9/5) + 32
```

The resulting temperature values are displayed on the 16×2 I2C LCD.

At the same time, the Arduino controls the RGB LED according to the configured temperature ranges. This provides a quick visual indication without needing to read the LCD continuously.

## Applications

An LM35 and Arduino-based temperature monitor can be used as a starting point for many electronics projects, including:

- Room temperature monitoring
- Temperature-controlled fans
- Electronics enclosure monitoring
- DIY weather stations
- Over-temperature warning systems
- Home automation projects
- Arduino-based environmental monitoring

## Project Reference

For the original tutorial, wiring diagram, detailed explanation, and related Arduino projects, visit:

**LM35 Temperature Sensor with Arduino Tutorial:**  
https://playwithcircuit.com/interfacing-lm35-temperature-sensor-with-arduino/

Play with Circuit publishes practical electronics and embedded-system tutorials covering **Arduino, ESP32, sensors, communication modules, displays, and DIY electronics projects**.

## Conclusion

The LM35 is a straightforward option when you need to add temperature sensing to an Arduino project. Its linear **10 mV/°C** output makes the sensor easy to read using the Arduino UNO's analog input.

By combining the LM35 with an I2C LCD and RGB LED, the basic sensor can be turned into a simple real-time temperature monitoring system that is useful for learning analog sensors as well as for small electronics projects.
