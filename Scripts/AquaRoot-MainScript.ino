/*
  AquaRoot - Automatic Plant Watering System
  Board: ESP32 DevKit V1 (ESP32-WROOM-32)
  PCB: KiCad custom design
  Author: Deadcode
  Github: https://github.com/DeddCode31251/AquaRoot/

  GPIO assignments:
    GPIO34 - Soil moisture sensor analog output
    GPIO25 - Pump MOSFET control
    GPIO27 - 2-pin water-level float switch
    GPIO21 - OLED SDA
    GPIO22 - OLED SCL
    GPIO32 - MODE button
    GPIO33 - SELECT button
    GPIO18 - Pump indicator LED
    GPIO4  - Active buzzer

  Button behavior:
    MODE   - Switch between AUTO and MANUAL
    SELECT - Start/stop pump in MANUAL mode

  Safety:
    - Pump disabled when water level is low
    - Maximum pump runtime
    - Cooldown between automatic watering cycles
    - Pump starts OFF

  IMPORTANT:
    Calibrate the soil sensor before using automatic watering.
    Verify the float switch behavior and pump driver before connecting
    the actual pump.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int SOIL_SENSOR_PIN = 34;
const int PUMP_PIN        = 25;
const int FLOAT_SWITCH_PIN = 27;

const int OLED_SDA_PIN = 21;
const int OLED_SCL_PIN = 22;

const int MODE_BUTTON_PIN   = 32;
const int SELECT_BUTTON_PIN = 33;

const int PUMP_LED_PIN = 18;
const int BUZZER_PIN   = 4;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);


int DRY_SOIL_RAW = 3000;
int WET_SOIL_RAW = 1400;

const int AUTO_START_MOISTURE = 30;
const int AUTO_STOP_MOISTURE = 45;
const unsigned long MAX_PUMP_RUNTIME = 10000UL; // 10 seconds
const unsigned long PUMP_COOLDOWN = 30000UL; // 30 seconds
const unsigned long DISPLAY_INTERVAL = 500UL;



const bool LOW_WATER_WHEN_SWITCH_CLOSED = true;


const bool BUZZER_ENABLED = true;

enum OperatingMode {
  AUTO_MODE,
  MANUAL_MODE
};

OperatingMode currentMode = AUTO_MODE;

bool pumpRunning = false;
bool manualPumpRequested = false;
bool lowWater = false;

int soilRaw = 0;
int soilMoisture = 0;

unsigned long pumpStartTime = 0;
unsigned long lastPumpStopTime = 0;
unsigned long lastDisplayUpdate = 0;

const unsigned long DEBOUNCE_DELAY = 40;

struct Button {
  int pin;
  bool lastReading;
  bool stableState;
  unsigned long lastChangeTime;
};

Button modeButton = {
  MODE_BUTTON_PIN,
  HIGH,
  HIGH,
  0
};

Button selectButton = {
  SELECT_BUTTON_PIN,
  HIGH,
  HIGH,
  0
};

bool buttonPressed(Button &button) {
  bool reading = digitalRead(button.pin);

  if (reading != button.lastReading) {
    button.lastChangeTime = millis();
    button.lastReading = reading;
  }

  if ((millis() - button.lastChangeTime) > DEBOUNCE_DELAY) {
    if (reading != button.stableState) {
      button.stableState = reading;

      if (button.stableState == LOW) {
        return true;
      }
    }
  }

  return false;
}


int readSoilSensor() {
  const int samples = 10;
  long total = 0;

  for (int i = 0; i < samples; i++) {
    total += analogRead(SOIL_SENSOR_PIN);
    delay(5);
  }

  return total / samples;
}

int calculateMoisturePercentage(int rawValue) {
  if (DRY_SOIL_RAW == WET_SOIL_RAW) {
    return 0;
  }

  int percentage = map(
    rawValue,
    DRY_SOIL_RAW,
    WET_SOIL_RAW,
    0,
    100
  );

  return constrain(percentage, 0, 100);
}

bool readLowWaterState() {
  bool switchClosed = (digitalRead(FLOAT_SWITCH_PIN) == LOW);

  if (LOW_WATER_WHEN_SWITCH_CLOSED) {
    return switchClosed;
  } else {
    return !switchClosed;
  }
}

void startPump() {
  if (lowWater) {
    Serial.println("Pump blocked: LOW WATER!");
    return;
  }

  if (pumpRunning) {
    return;
  }

  digitalWrite(PUMP_PIN, HIGH);
  digitalWrite(PUMP_LED_PIN, HIGH);

  if (BUZZER_ENABLED) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
  }

  pumpRunning = true;
  pumpStartTime = millis();

  Serial.println("Pump started.");
}

void stopPump() {
  if (!pumpRunning) {
    return;
  }

  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(PUMP_LED_PIN, LOW);

  pumpRunning = false;
  lastPumpStopTime = millis();

  Serial.println("Pump stopped.");
}

void handleButtons() {
  if (buttonPressed(modeButton)) {
    if (currentMode == AUTO_MODE) {
      currentMode = MANUAL_MODE;
      manualPumpRequested = false;
      stopPump();

      Serial.println("Mode changed: MANUAL");
    } else {
      currentMode = AUTO_MODE;
      manualPumpRequested = false;
      stopPump();

      Serial.println("Mode changed: AUTO");
    }
  }

  if (buttonPressed(selectButton)) {
    if (currentMode == MANUAL_MODE) {
      manualPumpRequested = !manualPumpRequested;

      if (manualPumpRequested) {
        Serial.println("Manual watering requested.");
      } else {
        Serial.println("Manual watering stopped.");
        stopPump();
      }
    } else {
      Serial.println("SELECT works only in MANUAL mode.");
    }
  }
}

void handleAutomaticWatering() {
  if (currentMode != AUTO_MODE) {
    return;
  }

  if (lowWater) {
    stopPump();
    return;
  }
  if (pumpRunning && soilMoisture >= AUTO_STOP_MOISTURE) {
    stopPump();
    return;
  }

  if (!pumpRunning && soilMoisture <= AUTO_START_MOISTURE) {
    bool cooldownFinished =
      (millis() - lastPumpStopTime) >= PUMP_COOLDOWN;

    if (cooldownFinished) {
      startPump();
    }
  }
}

void handleManualWatering() {
  if (currentMode != MANUAL_MODE) {
    return;
  }

  if (lowWater) {
    manualPumpRequested = false;
    stopPump();
    return;
  }

  if (manualPumpRequested && !pumpRunning) {
    startPump();
  }

  if (!manualPumpRequested && pumpRunning) {
    stopPump();
  }
}

void handlePumpSafety() {
  if (!pumpRunning) {
    return;
  }
  if (lowWater) {
    Serial.println("SAFETY: Low water detected.");
    manualPumpRequested = false;
    stopPump();
    return;
  }

  if ((millis() - pumpStartTime) >= MAX_PUMP_RUNTIME) {
    Serial.println("SAFETY: Maximum pump runtime reached.");

    manualPumpRequested = false;
    stopPump();
  }
}


void updateDisplay() {
  if ((millis() - lastDisplayUpdate) < DISPLAY_INTERVAL) {
    return;
  }

  lastDisplayUpdate = millis();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("AquaRoot Rev 1.0");

  display.setCursor(0, 12);

  if (currentMode == AUTO_MODE) {
    display.println("Mode: AUTO");
  } else {
    display.println("Mode: MANUAL");
  }

  display.setCursor(0, 24);
  display.print("Soil: ");
  display.print(soilMoisture);
  display.println("%");

  display.setCursor(0, 36);

  if (lowWater) {
    display.println("Water: LOW!");
  } else {
    display.println("Water: OK");
  }

  display.setCursor(0, 48);

  if (pumpRunning) {
    display.println("Pump: ON");
  } else {
    display.println("Pump: OFF");
  }

  display.display();
}


void printDebugInfo() {
  static unsigned long lastPrint = 0;

  if ((millis() - lastPrint) < 1000) {
    return;
  }

  lastPrint = millis();

  Serial.print("Raw: ");
  Serial.print(soilRaw);

  Serial.print(" | Moisture: ");
  Serial.print(soilMoisture);
  Serial.print("%");

  Serial.print(" | Low Water: ");
  Serial.print(lowWater ? "YES" : "NO");

  Serial.print(" | Mode: ");
  Serial.print(currentMode == AUTO_MODE ? "AUTO" : "MANUAL");

  Serial.print(" | Pump: ");
  Serial.println(pumpRunning ? "ON" : "OFF");
}


void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.println("==============================");
  Serial.println("AquaRoot Rev 1.0");
  Serial.println("Automatic Plant Watering");
  Serial.println("==============================");

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(PUMP_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(PUMP_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(FLOAT_SWITCH_PIN, INPUT_PULLUP);

  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);

  analogReadResolution(12);

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED initialization failed.");
    Serial.println("Check wiring and I2C address.");
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("AquaRoot");
    display.println("Initializing...");
    display.display();
  }

  soilRaw = readSoilSensor();
  soilMoisture = calculateMoisturePercentage(soilRaw);
  lowWater = readLowWaterState();

  lastPumpStopTime = millis();

  Serial.println("System initialized.");
  Serial.println("Pump is OFF.");
}


void loop() {
  soilRaw = readSoilSensor();
  soilMoisture = calculateMoisturePercentage(soilRaw);
  lowWater = readLowWaterState();
  handleButtons();
  handleAutomaticWatering();
  handleManualWatering();
  handlePumpSafety();
  updateDisplay();
  printDebugInfo();
  delay(10);
}
