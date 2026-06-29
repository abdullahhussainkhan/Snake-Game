# Snake Game — C++ Console

A classic Snake game built entirely in C++ for the Windows console. I originally wrote this as a side project and then came back to refurbish it properly — fixing bugs, adding features, and cleaning up the code structure until it was something I was genuinely proud of.

---

## What the game looks like

- Black console background with bright green snake, yellow food, and white double-line border
- ASCII title splash screen on startup
- Live HUD showing current score, best score, and speed level
- Smooth tile-by-tile movement with no screen flicker

---

## Features

- WASD and arrow key controls
- Pause and resume with P
- Dynamic speed — the snake gets faster every 10 points
- Food never spawns on the snake body (fixed with a retry loop)
- Persistent high score saved to `highscore.txt` and loaded on every startup
- Play again prompt after game over — no need to relaunch
- Clean game over screen showing final score, best score, and a new high score celebration message

---

## Controls

| Key | Action |
|---|---|
| W / Arrow Up | Move up |
| A / Arrow Left | Move left |
| S / Arrow Down | Move down |
| D / Arrow Right | Move right |
| P | Pause / Resume |
| Q | Quit |
| Y / N | Play again after game over |

---

## How to build and run

**Requirements:** Windows, g++ via MinGW/MSYS2

```bash
g++ main.cpp game.cpp snake.cpp food.cpp -o snake.exe
snake.exe
```
---

## Project structure

```
snake/
├── main.cpp       — Entry point, seeds the RNG once
├── game.cpp       — Game loop, input handling, rendering, score
├── game.h
├── snake.cpp      — Snake movement, growth, collision detection
├── snake.h
├── food.cpp       — Food spawning logic
├── food.h
├── config.h       — All constants in one place: board size, colors, speed
└── highscore.txt  — Created automatically on first run
```

---

## How this project was built

I originally wrote this game from scratch as a personal project to practice C++ and OOP. After leaving it for a while I came back to properly refurbish it with the help of AI.

## What I learned

- Windows Console API: cursor positioning with `SetConsoleCursorPosition`, color attributes with `SetConsoleTextAttribute`, screen buffer management with `FillConsoleOutputCharacter`
- Why uninitialized variables are dangerous and how to spot them
- How switch fallthrough works in C++ and when it is and isn't intentional
- The single source of truth principle — keeping one piece of logic in exactly one place
- How Windows encodes extended key presses as two-byte sequences
- File I/O with `fstream` for persistent data
- `const` correctness — marking methods and parameters `const` where they should be
- How to structure a multi-file C++ project cleanly with proper header guards

---

## Created by

Abdullah Hussain Khan — https://github.com/abdullahhussainkhan
