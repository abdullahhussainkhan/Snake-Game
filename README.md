Here's your README, ready to copy-paste directly into GitHub:

---

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

Or open in VS Code and press `Ctrl+Shift+B` to build, then `F5` to run in an external window.

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

I originally wrote this game from scratch as a personal project to practice C++ and OOP. After leaving it for a while I came back to properly refurbish it with the help of AI (Claude by Anthropic).

The AI helped me in a structured, phase-by-phase way rather than just rewriting everything for me. It reviewed my code, identified real bugs I had written, explained exactly why each one was a problem, and then guided me through fixing them one at a time. I made every change myself and understood each one before moving on.

Here is everything I worked through across the six phases:

**Phase 1 — Bug fixes:** The AI caught that `clearScreen()` was reading an uninitialized struct, which meant the console fill was covering a garbage-sized area. My `switch` statement in the input handler had no `break` statements, so pressing W would fall through all the way to Q and quit the game. `srand()` was being called inside the `Food` constructor instead of `main()`, which could cause identical random sequences. And the direction-reversal guard was duplicated in two places — the AI explained the "single source of truth" principle and we removed the redundant copy.

**Phase 2 — Arrow keys and pause:** I learned how Windows sends extended key codes as two bytes (first `0` or `224`, then the actual code) and wrote the two-byte read logic myself. Added a pause feature with a blocking wait loop that still allows quitting while paused.

**Phase 3 — Dynamic speed and food spawn fix:** Replaced the fixed `Sleep()` delay with a formula that scales speed with score. Fixed the food respawn function to actually use the existing `IsOnBody()` method I had already written but never connected — food would previously spawn on top of the snake.

**Phase 4 — Persistent high score:** Learned to use `ifstream` and `ofstream` to read and write a high score file. The game now remembers your best score across sessions.

**Phase 5 — Visual polish:** Replaced plain ASCII characters with extended ASCII box-drawing characters for the border (╔═╗║╚╝) and block characters for the snake body. Added a title splash screen, a play-again loop, and a new high score celebration message on the game over screen.

**Phase 6 — Code quality and structure:** Cleaned up headers, added `const` correctness to methods that don't modify state, moved all magic numbers into `config.h`, fixed `tasks.json` to compile all files at once instead of just the active file, and wrote this README.

---

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
