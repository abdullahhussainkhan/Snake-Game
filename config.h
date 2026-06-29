#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>

// Board inner dimensions 
const int BOARD_W = 60;
const int BOARD_H = 25;

// Console window size
const int CONSOLE_W = 120;
const int CONSOLE_H = 40;

//centre the board inside the console window
const int OFF_X = (CONSOLE_W - BOARD_W - 2) / 2;
const int OFF_Y = (CONSOLE_H - BOARD_H - 6) / 2;

// Speed constants 
const int SPEED_START = 140;
const int SPEED_MIN   =  55;
const int SPEED_STEP  =   3;

const WORD BG = 0;  // black background

const WORD COLOR_BORDER  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BG;
const WORD COLOR_SNAKE   = FOREGROUND_GREEN | FOREGROUND_INTENSITY | BG;
const WORD COLOR_FOOD    = FOREGROUND_RED | FOREGROUND_INTENSITY | BG;
const WORD COLOR_SCORE   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BG;
const WORD COLOR_DEFAULT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BG;
const WORD COLOR_BG      = BG;

#endif