#ifndef WORKER_CLOCK_CLOCK_DISPLAY_H
#define WORKER_CLOCK_CLOCK_DISPLAY_H

#include <LiquidCrystal.h>
#include "ElapsedTimer.h"
#include "config.h"

// Row assignments on the 16x2 LCD.
constexpr int ROW_WORK = 0;
constexpr int ROW_FREE = 1;

// Wraps the LCD and knows how to render the worker-clock layout:
//   Work=>00:00:00
//   Free=>00:00:00
class ClockDisplay {
 public:
  ClockDisplay()
      : lcd_(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6,
             PIN_LCD_D7) {}

  void begin();
  void showWelcome();
  void showGoodbye();
  void updateRow(int row, const ElapsedTimer& timer);

 private:
  void drawLabelsAndSeparators();
  void printTwoDigits(long value, int col, int row);

  LiquidCrystal lcd_;
};

#endif // WORKER_CLOCK_CLOCK_DISPLAY_H
