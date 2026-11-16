/*
  Railway Wagon Loading/Unloading Monitoring — starter sketch

  Example Arduino Uno wiring (verify before use):
    HX711 DT/DOUT -> D3
    HX711 SCK/CLK -> D2
    LCD SDA -> A4; LCD SCL -> A5

  Libraries: HX711 (e.g. Bogde) and compatible LiquidCrystal_I2C.

  IMPORTANT: Set the calibration factor using known reference masses.
  Set target load to the value used in your project. Example values below
  are placeholders, not measured specifications or railway limits.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

const byte HX711_DOUT_PIN = 3;
const byte HX711_SCK_PIN = 2;
const byte LCD_ADDRESS = 0x27; // Confirm with an I2C scanner.

float CALIBRATION_FACTOR = 1.0f; // PLACEHOLDER: calibrate your load cell.
const float TARGET_LOAD_KG = 5.0f; // PLACEHOLDER: set your project target.
const float TARGET_TOLERANCE_KG = 0.2f;
const float CHANGE_THRESHOLD_KG = 0.1f;

HX711 scale;
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
float previousWeight = 0.0f;
bool hasPreviousReading = false;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Wagon Load");

  scale.begin(HX711_DOUT_PIN, HX711_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR);
  delay(1500);

  if (scale.is_ready()) {
    // Start with an empty, stable platform.
    scale.tare();
    lcd.setCursor(0, 1);
    lcd.print("Scale tared");
    Serial.println("HX711 ready; tare completed.");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Check HX711");
    Serial.println("ERROR: HX711 not ready. Check wiring.");
  }
  delay(1000);
}

void loop() {
  if (!scale.is_ready()) {
    lcd.clear();
    lcd.print("Check HX711");
    delay(1000);
    return;
  }

  // This reads in kg only if calibration was performed using kg reference masses.
  float weightKg = scale.get_units(5);
  String movement = "STABLE";

  if (hasPreviousReading) {
    float delta = weightKg - previousWeight;
    if (delta > CHANGE_THRESHOLD_KG) movement = "LOADING";
    else if (delta < -CHANGE_THRESHOLD_KG) movement = "UNLOADING";
  }

  String loadStatus;
  if (weightKg < TARGET_LOAD_KG - TARGET_TOLERANCE_KG) loadStatus = "UNDER TARGET";
  else if (weightKg > TARGET_LOAD_KG + TARGET_TOLERANCE_KG) loadStatus = "OVER TARGET";
  else loadStatus = "TARGET REACHED";

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Load:");
  lcd.print(weightKg, 2);
  lcd.print(" kg");
  lcd.setCursor(0, 1);

  if (movement == "LOADING") lcd.print("Loading");
  else if (movement == "UNLOADING") lcd.print("Unloading");
  else if (loadStatus == "OVER TARGET") lcd.print("Over target");
  else if (loadStatus == "TARGET REACHED") lcd.print("Target reached");
  else lcd.print("Under target");

  Serial.print("Weight (calibrated units): ");
  Serial.println(weightKg, 3);
  Serial.print("Movement: ");
  Serial.println(movement);
  Serial.print("Load status: ");
  Serial.println(loadStatus);
  Serial.println("--------------------");

  previousWeight = weightKg;
  hasPreviousReading = true;
  delay(1000);
}
