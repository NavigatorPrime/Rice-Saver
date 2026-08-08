/*
 * RICE SAVER - Automated Grain Preservation System
 * Developer: Inuka Jithmal & Vihanga Nimsara
 * Hardware: Arduino Uno, DHT11/22, PIR Sensor, Relay, 16x2 I2C LCD, LEDs, Push Buttons
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- PIN DEFINITIONS ---
#define DHTPIN 4              // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11         // Change to DHT22 if you are using that version
#define PIR_PIN 2             // PIR Sensor pin (Must be Pin 2 or 3 for Interrupts on Uno)
#define RELAY_PIN 7           // Relay module controlling the Heater and Exhaust Fan
#define DANGER_LED 8          // Red LED for Danger alerts
#define VIEW_BTN 9            // Push button to view current Temp/Humid
#define ERADICATE_BTN 10      // Push button to manually trigger the 60°C cycle

// --- THRESHOLDS ---
const float MIN_SAFE_TEMP = 17.0;
const float MAX_SAFE_TEMP = 22.0;
const float MIN_SAFE_HUM = 35.0;
const float MAX_SAFE_HUM = 45.0;
const float ERADICATION_TEMP = 60.0;

// --- VARIABLES ---
volatile int motionCount = 0;
unsigned long lastMotionTime = 0;

bool isEradicating = false;
unsigned long eradicationStartTime = 0;
const unsigned long ERADICATION_DURATION = 7200000; // 2 hours in milliseconds

// Initialize DHT and LCD (Check your specific I2C address, usually 0x27 or 0x3F)
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(9600);
  
  // Pin Modes
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(DANGER_LED, OUTPUT);
  pinMode(VIEW_BTN, INPUT_PULLUP);
  pinMode(ERADICATE_BTN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);

  // Initialize Outputs
  digitalWrite(RELAY_PIN, LOW); // Relay OFF initially (Assuming Active HIGH)
  digitalWrite(DANGER_LED, LOW);
  
  // Attach hardware interrupt for the PIR sensor
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), countMotion, RISING);

  // Initialize Display & Sensor
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("RICE SAVER v1.0");
  lcd.setCursor(0, 1);
  lcd.print("System Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read sensor data
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  // Check if sensor readings are valid
  if (isnan(hum) || isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    return;
  }

  // --- BUTTON LOGIC ---
  bool viewBtnPressed = digitalRead(VIEW_BTN) == LOW;
  bool eradicateBtnPressed = digitalRead(ERADICATE_BTN) == LOW;

  if (eradicateBtnPressed && !isEradicating) {
    isEradicating = true;
    eradicationStartTime = millis();
    lcd.clear();
  }

  // --- ERADICATION MODE (60°C Cycle) ---
  if (isEradicating) {
    // Check if 2 hours have passed
    if (millis() - eradicationStartTime >= ERADICATION_DURATION) {
      isEradicating = false; // End cycle
      digitalWrite(RELAY_PIN, LOW); // Turn off heater/fan
      lcd.clear();
    } else {
      // Heat up to 60°C
      if (temp < ERADICATION_TEMP) {
        digitalWrite(RELAY_PIN, HIGH); // Turn Heater/Fan ON
      } else {
        digitalWrite(RELAY_PIN, LOW);  // Hold temp (Turn OFF briefly if it hits 60)
      }
      
      // Display Eradication Status
      lcd.setCursor(0, 0);
      lcd.print("ERADICATING PEST");
      lcd.setCursor(0, 1);
      lcd.print("Temp: ");
      lcd.print(temp);
      lcd.print("C   ");
    }
  } 
  // --- BASELINE MONITORING MODE ---
  else {
    digitalWrite(RELAY_PIN, LOW); // Ensure relay is off in normal mode

    bool tempDanger = (temp < MIN_SAFE_TEMP || temp > MAX_SAFE_TEMP);
    bool humDanger = (hum < MIN_SAFE_HUM || hum > MAX_SAFE_HUM);

    // Trigger LED if outside safe zones
    if (tempDanger || humDanger) {
      digitalWrite(DANGER_LED, HIGH);
    } else {
      digitalWrite(DANGER_LED, LOW);
    }

    // Display Logic based on View Button
    if (viewBtnPressed) {
      // Show exact readings when button is held
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(temp);
      lcd.print("C    ");
      
      lcd.setCursor(0, 1);
      lcd.print("Hum:  ");
      lcd.print(hum);
      lcd.print("%    ");
    } else {
      // Default Screen: Show Danger Warnings or Motion Count
      if (tempDanger || humDanger) {
        lcd.setCursor(0, 0);
        lcd.print(humDanger ? "Hum: DANGER!    " : "Hum: SAFE       ");
        lcd.setCursor(0, 1);
        lcd.print(tempDanger ? "Temp: DANGER!   " : "Temp: SAFE      ");
      } else {
        lcd.setCursor(0, 0);
        lcd.print("System: SAFE    ");
        lcd.setCursor(0, 1);
        lcd.print("Motion Count: ");
        lcd.print(motionCount);
        lcd.print("  "); // Clear trailing characters
      }
    }
  }
}

// --- PIR SENSOR INTERRUPT SERVICE ROUTINE ---
void countMotion() {
  unsigned long currentTime = millis();
  // Simple software debounce: only count once every 2 seconds
  if (currentTime - lastMotionTime > 2000) {
    motionCount++;
    lastMotionTime = currentTime;
  }
}