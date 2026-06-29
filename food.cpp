#include "food.h"

Food::Food() {
    x = BOARD_W / 4;
    y = BOARD_H / 4;
}

int Food::getX() const { return x; }
int Food::getY() const { return y; }

// keep rolling until we land on a free cell. in the worst case (snake fills almost the whole board) this loop runs many times, but that only happens near the end of a very long game it is not a performance concern in practice.
void Food::respawn(int boardW, int boardH, const Snake& snake) {
    do {
        x = (rand() % (boardW - 2)) + 1;   // boardW-2  (inside border)
        y = (rand() % (boardH - 2)) + 1;   // boardH-2
    } while (snake.IsOnBody(x, y));         // retry if cell is occupied
}

void Food::draw(HANDLE console) const {
    COORD pos;
    pos.X = x + OFF_X;
    pos.Y = y + OFF_Y;
    SetConsoleCursorPosition(console, pos);
    cout << char(36);   // '$'
}