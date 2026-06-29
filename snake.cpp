#include "snake.h"

Snake::Snake() {
    length = 3;
    dir    = RIGHT;
    body[0] = { BOARD_W / 2 + 1, BOARD_H / 2 };
    body[1] = { BOARD_W / 2,     BOARD_H / 2 };
    body[2] = { BOARD_W / 2 - 1, BOARD_H / 2 };
}

int       Snake::getX()         const { return body[0].x; }
int       Snake::getY()         const { return body[0].y; }
int       Snake::getLength()    const { return length; }
Direction Snake::getDirection() const { return dir; }

void Snake::setDirection(Direction newDir) {
    if (newDir == UP    && dir == DOWN)  return;
    if (newDir == DOWN  && dir == UP)    return;
    if (newDir == LEFT  && dir == RIGHT) return;
    if (newDir == RIGHT && dir == LEFT)  return;
    dir = newDir;
}

void Snake::move() {
    for (int i = length - 1; i > 0; i--)
        body[i] = body[i - 1];
    if (dir == UP)    body[0].y--;
    if (dir == DOWN)  body[0].y++;
    if (dir == LEFT)  body[0].x--;
    if (dir == RIGHT) body[0].x++;
}

void Snake::grow() {
    if (length < 100) length++;
}

bool Snake::hitSelf() const {
    for (int i = 1; i < length; i++)
        if (body[0].x == body[i].x && body[0].y == body[i].y)
            return true;
    return false;
}

bool Snake::IsOnBody(int x, int y) const {
    for (int i = 0; i < length; i++)
        if (body[i].x == x && body[i].y == y)
            return true;
    return false;
}

void Snake::draw(HANDLE console) const {
    COORD pos;
    for (int i = 0; i < length; i++) {
        pos.X = body[i].x + OFF_X;
        pos.Y = body[i].y + OFF_Y;
        SetConsoleCursorPosition(console, pos);
        cout << (i == 0 ? char(219) : char(254));
    }
}

void Snake::erase(HANDLE console) const {
    COORD pos;
    pos.X = body[length - 1].x + OFF_X;
    pos.Y = body[length - 1].y + OFF_Y;
    SetConsoleCursorPosition(console, pos);
    SetConsoleTextAttribute(console, COLOR_BG);
    cout << ' ';
}