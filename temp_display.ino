/* 
Interfacing temperature Sensor with Arduino UNO using Analog input pin of Arduino and 
displaying of temperature in fahrenheit and in degree Celcius on I2C LCD. There is one
multicolor LED turns which turns Blue at LOW temperature , Red at HIGH tempearature 
and Green when the temperature is between LOW and HIGH limit.
by www.playwithcircuit.com
*/

#include <LiquidCrystal_I2C.h>  // Library to Run I2C LCD

#define RED_PIN 10
#define BLUE_PIN 9
#define GREEN_PIN 8


#define LOW_TEMP    10
#define HIGH_TEMP   50
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the analog pin for the soil moisture sensor
const int TemperatureSensorPin = A0;

// Variable to store the Analog count from temperature sensor
int temperatureCounts;

// Variables to store Voltage values
float voltageValue;

// Vaiable to Store Temperature in Degree Celcius
float temperatureDegreeCelcius;

// Vaiable to Store Temperature in fahrenheit Celcius
float temperatureFahrenheit;

void setup() {
  // initialize the lcd
  lcd.init();
  // Turn on the Backlight
  lcd.backlight();
  // Clear the display buffer
  lcd.clear();
  // Make LED pins and Buzzer pin as output
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // Turn Off all the pins
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);

  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Initializing");

  // Print a message to the LCD
  lcd.setCursor(0, 1);
  lcd.print("Please Wait...");

  // flush out the first hundred values give time to temeprarture sensor to be stable
  for (int i = 0; i < 100; i++) {
    // Read the value from the temperature sensor
    temperatureCounts = analogRead(TemperatureSensorPin);
    delay(10);
  }
  // Clear the display buffer
  lcd.clear();

  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp in C:");

  // Print a message to the LCD
  lcd.setCursor(0, 1);
  lcd.print("Temp in F:");
}

void loop() {
  // Static variables to save the last temperature
  static float lastTemp = 0xFF;

  // Read the value from the temperature sensor
  temperatureCounts = analogRead(TemperatureSensorPin);

  // covert the counts 0 to 1023 into voltage values 0 to 5V
  voltageValue = (5.0/1023) * temperatureCounts;

  // Convert voltage to temperature in Celsius
  temperatureDegreeCelcius = voltageValue * 100;

  // Convert Celsius to Fahrenheit
  temperatureFahrenheit = (temperatureDegreeCelcius * 9.0 / 5.0) + 32.0;


  // If current tempearure is not equal to last tempearure value in degree celcius
  if (lastTemp != temperatureDegreeCelcius) {
    // Print a temp to the LCD
    lcd.setCursor(10, 0);
    lcd.print("      ");
    lcd.setCursor(10, 0);
    lcd.print((int)temperatureDegreeCelcius);

    // Print a message to the LCD
    lcd.setCursor(10, 1);
    lcd.print("      ");
    lcd.setCursor(10, 1);
    lcd.print((int)temperatureFahrenheit);
  }

  // Save the cureent tempearature value in the static varibale to use it later
  lastTemp = temperatureDegreeCelcius;

  // Change the color of LED as per temperature level
  if (temperatureDegreeCelcius > HIGH_TEMP) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  } else if (temperatureDegreeCelcius >= LOW_TEMP && temperatureDegreeCelcius <= HIGH_TEMP) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  } else if (temperatureDegreeCelcius < LOW_TEMP) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  }

  // Wait for 10 ms before the next loop
  delay(20);
}
