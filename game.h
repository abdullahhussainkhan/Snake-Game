#ifndef GAME_H
#define GAME_H

//the snake, food, score, and high score

#include "snake.h"
#include "food.h"
#include "config.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Game {
private:
    Snake  snake;
    Food   food;
    int    score;
    int    highScore;   
    bool   running;
    bool   paused;      
    HANDLE console;

    void gotoxy(int x, int y);
    void hideCursor();
    void setColor(WORD color);
    void clearScreen();
    int  getSpeed() const;   

    void drawBorder();
    void drawScore();
    void drawSplash();       
    void drawPauseScreen();  
    void erasePauseScreen();

    void handleInput();
    void update();
    void gameOver();

    void loadHighScore();    
    void saveHighScore();   

public:
    Game();
    void run();
};

#endif