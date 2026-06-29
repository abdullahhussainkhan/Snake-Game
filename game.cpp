#include "game.h"

Game::Game() {
    score     = 0;
    running   = true;
    paused    = false;
    console   = GetStdHandle(STD_OUTPUT_HANDLE);
    loadHighScore();   // read best score from disk
}

void Game::gotoxy(int x, int y) {
    COORD c;
    c.X = x + OFF_X;
    c.Y = y + OFF_Y;
    SetConsoleCursorPosition(console, c);
}

void Game::hideCursor() {
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize   = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(console, &ci);
}

void Game::setColor(WORD color) {
    SetConsoleTextAttribute(console, color);
}

void Game::clearScreen() {
    COORD topLeft = {0, 0};
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);          
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputAttribute(console, COLOR_BG, size, topLeft, &written);
    FillConsoleOutputCharacter(console, ' ',      size, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

// Every 10 points shaves SPEED_STEP ms off the delay, down to SPEED_MIN.
// Vertical movement gets +30 ms so it feels balanced with horizontal.
int Game::getSpeed() const {
    int base = max(SPEED_MIN, SPEED_START - (score / 10) * SPEED_STEP);
    Direction d = snake.getDirection();
    return (d == UP || d == DOWN) ? base + 30 : base;
}

void Game::loadHighScore() {
    highScore = 0;
    ifstream f("highscore.txt");
    if (f.is_open()) {
        f >> highScore;
        f.close();
    }
}

void Game::saveHighScore() {
    if (score > highScore) {
        highScore = score;
        ofstream f("highscore.txt");
        if (f.is_open()) {
            f << highScore;
            f.close();
        }
    }
}

// border
void Game::drawBorder() {
    setColor(COLOR_BORDER);
    gotoxy(0, 0);
    for (int i = 0; i <= BOARD_W + 1; i++) cout << char(205);  // ═
    gotoxy(0, BOARD_H + 1);
    for (int i = 0; i <= BOARD_W + 1; i++) cout << char(205);  // ═
    for (int i = 1; i <= BOARD_H; i++) {
        gotoxy(0,           i); cout << char(186);              // ║
        gotoxy(BOARD_W + 1, i); cout << char(186);              // ║
    }
    // Corners
    gotoxy(0,           0);        cout << char(201);           // ╔
    gotoxy(BOARD_W + 1, 0);        cout << char(187);           // ╗
    gotoxy(0,           BOARD_H+1);cout << char(200);           // ╚
    gotoxy(BOARD_W + 1, BOARD_H+1);cout << char(188);           // ╝
    setColor(COLOR_DEFAULT);
}

void Game::drawScore() {
    setColor(COLOR_SCORE);
    gotoxy(0, BOARD_H + 3);
    cout << "Score: " << score << "   Best: " << highScore << "   ";
    gotoxy(0, BOARD_H + 4);
    cout << "W/A/S/D or Arrows = move  |  P = Pause  |  Q = Quit   ";
    int level = (score / 10) + 1;
    gotoxy(0, BOARD_H + 5);
    cout << "Speed level: " << level << "   ";
    setColor(COLOR_DEFAULT);
}

void Game::drawSplash() {
    clearScreen();
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);

    int cx = BOARD_W / 2 - 13;
    int cy = BOARD_H / 2 - 5;

    gotoxy(cx,     cy);   cout << "  ███████╗███╗  ██╗ █████╗ ██╗  ██╗███████╗";
    gotoxy(cx,     cy+1); cout << "  ██╔════╝████╗ ██║██╔══██╗██║ ██╔╝██╔════╝";
    gotoxy(cx,     cy+2); cout << "  ███████╗██╔██╗██║███████║█████╔╝ █████╗  ";
    gotoxy(cx,     cy+3); cout << "  ╚════██║██║╚████║██╔══██║██╔═██╗ ██╔══╝  ";
    gotoxy(cx,     cy+4); cout << "  ███████║██║ ╚███║██║  ██║██║  ██╗███████╗";
    gotoxy(cx,     cy+5); cout << "  ╚══════╝╚═╝  ╚══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝";

    setColor(COLOR_SCORE);
    gotoxy(BOARD_W / 2 - 10, cy + 8);
    cout << "Best score: " << highScore;

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    gotoxy(BOARD_W / 2 - 11, cy + 10);
    cout << "Press any key to start...";

    setColor(COLOR_DEFAULT);
    getch();
}

void Game::drawPauseScreen() {
    int cx = BOARD_W / 2 - 11;
    int cy = BOARD_H / 2 - 1;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    gotoxy(cx, cy);     cout << "+--------------------+";
    gotoxy(cx, cy + 1); cout << "|      ~ PAUSED ~    |";
    gotoxy(cx, cy + 2); cout << "|  Press P to resume |";
    gotoxy(cx, cy + 3); cout << "+--------------------+";
    setColor(COLOR_DEFAULT);
}

void Game::erasePauseScreen() {
    int cx = BOARD_W / 2 - 11;
    int cy = BOARD_H / 2 - 1;
    setColor(COLOR_BG);
    for (int row = 0; row < 4; row++) {
        gotoxy(cx, cy + row);
        cout << "                      "; 
    }
    setColor(COLOR_DEFAULT);
    // immediately restore food and snake
    setColor(COLOR_FOOD);
    food.draw(console);
    setColor(COLOR_SNAKE);
    snake.draw(console);
    setColor(COLOR_DEFAULT);
}

void Game::handleInput() {
    if (!kbhit()) return;

    int key = getch();

    // arrow keys: windows sends 0 or 224
    if (key == 0 || key == 224) {
        key = getch();
        if (!paused) {
            switch (key) {
                case 72: snake.setDirection(UP);    break;
                case 80: snake.setDirection(DOWN);  break;
                case 75: snake.setDirection(LEFT);  break;
                case 77: snake.setDirection(RIGHT); break;
            }
        }
        return;
    }

    switch (key) {
        case 'w': case 'W': if (!paused) snake.setDirection(UP);    break;
        case 's': case 'S': if (!paused) snake.setDirection(DOWN);  break;
        case 'a': case 'A': if (!paused) snake.setDirection(LEFT);  break;
        case 'd': case 'D': if (!paused) snake.setDirection(RIGHT); break;

        case 'p': case 'P':
            paused = !paused;
            if (paused) {
                drawPauseScreen();
                while (paused) {
                    if (kbhit()) {
                        int k = getch();
                        if (k == 'p' || k == 'P') { paused = false; erasePauseScreen(); }
                        if (k == 'q' || k == 'Q') { paused = false; running = false; }
                    }
                    Sleep(50);
                }
            }
            break;

        case 'q': case 'Q': running = false; break;
    }
}

void Game::update() {
    snake.erase(console);
    snake.move();

    // Wall collision
    if (snake.getX() <= 0 || snake.getX() >= BOARD_W + 1 ||
        snake.getY() <= 0 || snake.getY() >= BOARD_H + 1) {
        running = false;
        return;
    }

    // Self collision
    if (snake.hitSelf()) {
        running = false;
        return;
    }

    // Food eaten
    if (snake.getX() == food.getX() && snake.getY() == food.getY()) {
        score += 10;
        snake.grow();
        food.respawn(BOARD_W, BOARD_H, snake);  
        setColor(COLOR_FOOD);
        food.draw(console);
        drawScore();
    }

    setColor(COLOR_SNAKE);
    snake.draw(console);
    setColor(COLOR_DEFAULT);
}

// Game over
void Game::gameOver() {
    saveHighScore();   // Phase 4

    bool newRecord = (score >= highScore && score > 0);

    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    gotoxy(BOARD_W / 2 - 9,  BOARD_H / 2);
    cout << " *** GAME OVER *** ";
    gotoxy(BOARD_W / 2 - 9,  BOARD_H / 2 + 1);
    cout << "Final score : " << score << "   ";
    gotoxy(BOARD_W / 2 - 9,  BOARD_H / 2 + 2);
    cout << "Best score  : " << highScore << "   ";

    if (newRecord) {
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
        gotoxy(BOARD_W / 2 - 9, BOARD_H / 2 + 3);
        cout << "** New high score! **";
    }

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    gotoxy(BOARD_W / 2 - 11, BOARD_H / 2 + 5);
    cout << "Play again? (Y = yes  /  N = exit)";
    setColor(COLOR_DEFAULT);

    while (true) {
        int k = getch();
        if (k == 'y' || k == 'Y') {
            // Reset state and restart
            score   = 0;
            running = true;
            paused  = false;
            snake   = Snake();
            food    = Food();
            run();   // recursive call
            return;
        }
        if (k == 'n' || k == 'N') return;
    }
}

// game loop
void Game::run() {
    system("mode con: cols=120 lines=40");

    drawSplash();   

    clearScreen();
    hideCursor();
    drawBorder();

    setColor(COLOR_FOOD);
    food.draw(console);
    setColor(COLOR_SNAKE);
    snake.draw(console);
    drawScore();

    while (running) {
        handleInput();
        if (!running) break;
        if (paused)   continue;

        update();
        Sleep(getSpeed());   
    }

    gameOver();
}