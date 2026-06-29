#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <windows.h>
#include "config.h"
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct BodyPart {
    int x, y;
};

class Snake {
private:
    BodyPart  body[100];
    int       length;
    Direction dir;

public:
    Snake();

    // getters
    int       getX()         const;
    int       getY()         const;
    int       getLength()    const;
    Direction getDirection() const;

    //setter
    void setDirection(Direction newDir);

    // actions
    void move();
    void grow();

    // collision checks
    bool hitSelf()              const;
    bool IsOnBody(int x, int y) const;  // used by Food::respawn()

    //rendering
    void draw (HANDLE console) const;
    void erase(HANDLE console) const;
};

#endif