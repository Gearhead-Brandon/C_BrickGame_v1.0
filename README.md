# BrickGame v1.0 - Tetris

## Project Requirements

### Part 1: Core Features  
- Developed in C11 using `gcc` compiler.  
- Two main components:  
  - **Library** implementing Tetris logic (`src/brick_game/tetris`).  
  - **CLI interface** using `ncurses` (`src/gui/cli`).  
- Implements a **finite state machine (FSM)** for game logic.  
- Library functions:  
  - Handles user input.  
  - Provides a matrix representation of the game field.  
- Built using **Makefile** with standard GNU targets (`all, install, uninstall, clean, etc.`).  
- **Google Style Guide** compliance.  
- **Unit tests** (80%+ coverage) using `check` (supports Darwin/Ubuntu).  

### Gameplay Mechanics  
- **Tetromino control:** Rotate, move horizontally, hard drop.  
- **Game field:** 10x20 grid.  
- **Full-line clearing** with score accumulation.  
- **Game over** when reaching the top.  
- **Preview of the next piece.**  
- **Physical console button support:**  
  - Start, Pause, End.  
  - Left/Right (move), Down (drop), Action (rotate).  

### Part 2: Score & High Score System  
- Scoring:  
  - 1 line = **100** points  
  - 2 lines = **300** points  
  - 3 lines = **700** points  
  - 4 lines = **1500** points  
- High score stored in a file or database and persists between sessions.  

### Part 3: Level Mechanic  
- Level increases every **600 points** (max level 10).  
- Higher levels increase **falling speed** of pieces.  