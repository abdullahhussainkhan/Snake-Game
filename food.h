#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "config.h"
#include "snake.h"
using namespace std;

class Food {
private:
    int x, y;
public:
    Food();

    int getX() const;
    int getY() const;

    void respawn(int boardW, int boardH, const Snake& snake);

    void draw(HANDLE console) const;
};

#endif