#include <Arduino.h>
#include "ClockDisplay.h"

namespace {
constexpr int kTimeStartCol = 7;   // Column where "HH:MM:SS" begins.
constexpr int kColonAfterHours = 9;
constexpr int kColonAfterMinutes = 12;
}  // namespace

void ClockDisplay::begin() {
  lcd_.begin(16, 2);
}

void ClockDisplay::showWelcome() {
  lcd_.clear();
  lcd_.print(F("Hello, Luke!"));
  delay(1500);
  lcd_.clear();
  lcd_.print(F("Beautiful day!"));
  lcd_.setCursor(0, 1);
  lcd_.print(F("Is't it?"));
  delay(1500);
  lcd_.clear();
  drawLabelsAndSeparators();
}

void ClockDisplay::showGoodbye() {
  lcd_.clear();
  lcd_.print(F("Good Bye Luke!"));
  delay(1500);
  lcd_.clear();
}

void ClockDisplay::drawLabelsAndSeparators() {
  lcd_.setCursor(0, ROW_WORK);
  lcd_.print(F("Work=>"));
  lcd_.setCursor(0, ROW_FREE);
  lcd_.print(F("Free=>"));

  const int rows[] = {ROW_WORK, ROW_FREE};
  for (unsigned i = 0; i < 2; i++) {
    lcd_.setCursor(kColonAfterHours, rows[i]);
    lcd_.print(':');
    lcd_.setCursor(kColonAfterMinutes, rows[i]);
    lcd_.print(':');
  }
}

void ClockDisplay::updateRow(int row, const ElapsedTimer& timer) {
  printTwoDigits(timer.hours(), kTimeStartCol, row);
  printTwoDigits(timer.minutes(), kTimeStartCol + 3, row);
  printTwoDigits(timer.seconds(), kTimeStartCol + 6, row);
}

void ClockDisplay::printTwoDigits(long value, int col, int row) {
  lcd_.setCursor(col, row);
  if (value < 10) {
    lcd_.print('0');
    lcd_.setCursor(col + 1, row);
  }
  lcd_.print(value);
}
