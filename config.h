#ifndef WORKER_CLOCK_CONFIG_H
#define WORKER_CLOCK_CONFIG_H

// LCD pin wiring (see README for the physical circuit).
constexpr int PIN_LCD_RS = 12;
constexpr int PIN_LCD_EN = 11;
constexpr int PIN_LCD_D4 = 5;
constexpr int PIN_LCD_D5 = 4;
constexpr int PIN_LCD_D6 = 3;
constexpr int PIN_LCD_D7 = 2;

// Control pins.
constexpr int PIN_POWER_SUPPLY = 7;   // Keeps the device powered while HIGH.
constexpr int PIN_MODE_BUTTON = 8;    // Toggles between work/free timers.
constexpr int PIN_LED_GREEN = 9;      // Lit while in "free time" mode.
constexpr int PIN_LED_RED = 10;       // Lit while in "work time" mode.
constexpr int PIN_POWER_OFF = 13;     // Signals the power supply to cut off.

// Timing constants.
constexpr long SECONDS_PER_MINUTE = 60;
constexpr long AUTO_SHUTDOWN_AFTER_SECONDS = 60; // Total uptime before auto power-off.

#endif // WORKER_CLOCK_CONFIG_H
