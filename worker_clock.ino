/*
  Worker Clock
  ------------
  Dual-mode stopwatch (Work / Free time) displayed on a 16x2 LCD, with a
  push button to switch modes and an auto power-off after a fixed uptime.

  Circuit:
  - LCD RS   -> digital pin 12
  - LCD EN   -> digital pin 11
  - LCD D4   -> digital pin 5
  - LCD D5   -> digital pin 4
  - LCD D6   -> digital pin 3
  - LCD D7   -> digital pin 2
  - LCD R/W  -> GND
  - LCD VSS  -> GND
  - LCD VCC  -> 5V
  - 10K potentiometer: ends to +5V/GND, wiper to LCD VO (contrast)
*/

#include "config.h"
#include "ElapsedTimer.h"
#include "ClockDisplay.h"

ClockDisplay display;
ElapsedTimer workTimer;
ElapsedTimer freeTimer;

bool isWorkMode = true;
long lastTickSecond = -1;

void setMode(bool workMode) {
  isWorkMode = workMode;
  digitalWrite(PIN_LED_RED, workMode ? HIGH : LOW);
  digitalWrite(PIN_LED_GREEN, workMode ? LOW : HIGH);
}

void handleModeButton() {
  if (digitalRead(PIN_MODE_BUTTON) != HIGH) {
    return;
  }
  delay(20);  // Debounce.
  setMode(!isWorkMode);
  while (digitalRead(PIN_MODE_BUTTON) == HIGH) {
    // Wait for the button to be released.
  }
  delay(20);  // Debounce.
}

void shutDown() {
  display.showGoodbye();
  digitalWrite(PIN_POWER_SUPPLY, LOW);
  delay(500);
  digitalWrite(PIN_POWER_OFF, HIGH);
  delay(500);
}

void advanceTimersOncePerSecond() {
  long uptimeSeconds = millis() / 1000;
  if (uptimeSeconds <= lastTickSecond) {
    return;
  }
  lastTickSecond = uptimeSeconds;

  ElapsedTimer& activeTimer = isWorkMode ? workTimer : freeTimer;
  activeTimer.tick();
  display.updateRow(isWorkMode ? ROW_WORK : ROW_FREE, activeTimer);

  if (uptimeSeconds > AUTO_SHUTDOWN_AFTER_SECONDS) {
    shutDown();
  }
}

void setup() {
  pinMode(PIN_MODE_BUTTON, INPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_POWER_OFF, OUTPUT);
  pinMode(PIN_POWER_SUPPLY, OUTPUT);
  digitalWrite(PIN_POWER_OFF, LOW);
  digitalWrite(PIN_POWER_SUPPLY, HIGH);

  display.begin();
  display.showWelcome();
  setMode(isWorkMode);
}

void loop() {
  handleModeButton();
  advanceTimersOncePerSecond();
}
