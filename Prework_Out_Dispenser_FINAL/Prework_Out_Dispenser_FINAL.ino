#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711_ADC.h>

// LCD setup (adjust the I2C address if necessary)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button pin definitions
const int buttonWaterPin = 4;   // GPIO 4 for "Dispensing water"
const int buttonPowderPin = 5;  // GPIO 5 for "Dispensing powder"

// Variables to store the last button states
int lastButtonWaterState = HIGH;
int lastButtonPowderState = HIGH;

//pump Pins
const int pumpIn1 = 18;    // IN1 on L293D
const int pumpIn2 = 19;    // IN2 on L293D

//Powder Pins
const int powderIn1 = 26;
const int powderIn2 = 27;

//HX711 Pins
const int loadDT = 33;
const int loadSCK = 32;

HX711_ADC LoadCell(loadDT,loadSCK);

void setup() {
  // Initialize Serial Monitor (optional, for debugging)
  Serial.begin(115200);

  // Initialize the LCD
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the backlight
  lcd.clear();         // Clear the display
  lcd.setCursor(0, 0);
  lcd.print("Pre-workout");
  lcd.setCursor(0, 1);
  lcd.print("mixer");

  // Initialize buttons with internal pull-up resistors
  pinMode(buttonWaterPin, INPUT_PULLUP);
  pinMode(buttonPowderPin, INPUT_PULLUP);
// Initialize  pump pins
  pinMode(pumpIn1, OUTPUT);
  pinMode(pumpIn2, OUTPUT);

   // Initialize powder dispenser pins
  pinMode(powderIn1, OUTPUT);
  pinMode(powderIn2, OUTPUT);

  // Initialize the load cell
  LoadCell.begin();
  float calibration_factor = -5242.56; // Adjust this value according to calibration
  LoadCell.setCalFactor(calibration_factor);

  // Start HX711, make sure we wait until it's ready
  unsigned long stabilizingTime = 2000; // Stabilizing time in milliseconds
  LoadCell.start(stabilizingTime);
  LoadCell.tare(); // Reset the scale to zero

  Serial.println("Load cell initialized.");
}

void loop() {
  // Read the state of the buttons
  int buttonWaterState = digitalRead(buttonWaterPin);
  int buttonPowderState = digitalRead(buttonPowderPin);

  //update scale
  LoadCell.update();

  // Check if the Water button was pressed
  if (buttonWaterState == LOW && lastButtonWaterState == HIGH) {
    // Button was just pressed
    Serial.println("Water button pressed");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dispensing");
    lcd.setCursor(0, 1);
    lcd.print("water");

    // Activate the water dispensing mechanism
    dispenseWater();
    // startPump();
    // delay(4000); // Dispense water for 4 seconds
    // stopPump();

    delay(2000);  // Display message for 2 seconds
    resetDisplay();
  }

  // Check if the Powder button was pressed
  if (buttonPowderState == LOW && lastButtonPowderState == HIGH) {
    // Button was just pressed
    Serial.println("Powder button pressed");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dispensing");
    lcd.setCursor(0, 1);
    lcd.print("powder");

    // Add code here to activate the powder dispensing mechanism
    dispensePowder();

    delay(2000);  // Display message for 2 seconds
    resetDisplay();
  }

  // Update the last button states
  lastButtonWaterState = buttonWaterState;
  lastButtonPowderState = buttonPowderState;

  // Small delay to debounce buttons
  delay(50);
}

// Function to reset the display to the initial message
void resetDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pre-workout");
  lcd.setCursor(0, 1);
  lcd.print("mixer");
}

// Function to start the pump
void startPump() {
  // Set motor direction
  digitalWrite(pumpIn1, HIGH);
  digitalWrite(pumpIn2, LOW);
  // If using PWM for speed control, set pumpEnable accordingly
  Serial.println("Pump started");
}

// Function to stop the pump
void stopPump() {
  // Stop the motor
  digitalWrite(pumpIn1, LOW);
  digitalWrite(pumpIn2, LOW);
  Serial.println("Pump stopped");
}

// Function to start the powder dispenser
void startPowderDispenser() {
  // Set motor direction
  digitalWrite(powderIn1, HIGH);
  digitalWrite(powderIn2, LOW);
  // If using PWM for speed control, set powderEnable accordingly
  Serial.println("Powder dispenser started");
}

// Function to stop the powder dispenser
void stopPowderDispenser() {
  // Stop the motor
  digitalWrite(powderIn1, LOW);
  digitalWrite(powderIn2, LOW);
  Serial.println("Powder dispenser stopped");
}

//Function to dispense water for proper weight(7oz)
void dispenseWater(){
  float targetWeightOunces = 13.0;
  float targetWeightGrams = targetWeightOunces * 28.3495;

  // Tare the scale and wait for stabilization
  LoadCell.tare();
  delay(500); // Allow time for taring to complete and stabilize

  startPump();

  while(true){
    LoadCell.update();
    float currentWeight = LoadCell.getData();
    Serial.print("Current Weight (Water): ");
    Serial.println(currentWeight);

    if (currentWeight >= targetWeightGrams) {
      stopPump();
      Serial.println("Target weight for water reached.");
      break;
    }
    delay(100); // Small delay to prevent overload
  }
}

//Function to dispense powder for proper weight(20g)
void dispensePowder(){
  float targetWeightGrams = 200.0;

  LoadCell.tare();
  delay(500);
  startPowderDispenser();

  while(true){
    LoadCell.update();
    float currentWeight = LoadCell.getData();
    Serial.print("Current Weight (Powder): ");
    Serial.print(currentWeight);

    if (currentWeight >= targetWeightGrams) {
      stopPowderDispenser();
      Serial.println("Target weight for powder reached.");
      break;
    }
    delay(100); // Small delay to prevent overload



  }
}

