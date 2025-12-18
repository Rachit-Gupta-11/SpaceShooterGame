**Clash of Titans**
**By Rachit Gupta : 240150027**
**Welcome Project****

A terminal-based shooter game written in C++ featuring multiple weapons, enemies and bombs

**Game Overview**

Clash of Titans is a classic arcade game where you control a spaceship at the bottom of the screen represented as "/i\" , and shoot the incoming randomly spawning enemy planes. you can use multiple weapon types, powerups and even a Nuke!!!

**Features**

### Core Gameplay
- Player Movement: Control your spaceship with left and right arrow keys. By pressing spacebar you can toggle the Fast mode to move quicker or slower.
- Multiple Weapon Types:
  - Standard bullets (Up Arrow)
  - Splitter bullets (Down Arrow) - split into horizontal projectiles on enemy hit
- Enemies: Enemy continuosly keep on spawning and shooting downwards randomly.
- Level System: 3 difficulty levels which keeps on getting harder by spawning enemies and their bullets at higher rate

### Power-ups & Items
- Medikits: If the player loses a life and hits a medikit represent by "M" he instantly heals that life. Cannot be hit with splitter bullets. Do not appear if score is greater than 500.
- Extra Points: Bonus 50 points when hit. Represented by a + sign. Cannot be hit with spliiter bullets. Do not appear when score is more than 500
- Bombs: Represented as a "o" and reduce one life if hit. stats in level 2 and appears more in level 3.
- Nukes: Clear all enemies on screen and adds points for each enemy. Can only be used 3 times per game

### Game Mechanics
- Score System: 10 Points for destroying enemies.
- Lives System: Start with 3 lives, game over when all lives are lost. 



###Controls
 Left Arrow - Move left 
 Right Arrow - Move right 
 Up Arrow - Fire standard bullet 
 Down Arrow - Fire splitter bullet 
 Spacebar - Toggle fast mode 
 Enter - Use nuke
 Q or ESC - Quit game 


**Installation & Build**

### Prerequisites
- g++ compiler with C++17 or later.
- Make utility
- Unix terminal i.e Ubuntu or MacOS

### Building the Game

1. Download the project files

2. Compile the game:
   ```bash
   make
   ```

3. Run the game*
   ```bash
   make run
   ```
   or
   ```bash
   ./game
   ```

### Build Options

- Clean build artifacts:
  ```bash
  make clean
  ```

- Compile and run in one command:
  ```bash
  make run
  ```

## Structure

The game includes the following files.
  ─ main.cpp                        # Main logic and looops
  ─ player.h and player.cpp         # Player variables
  ─ enemy.h and enemy.cpp           # Enemy variables
  ─ bullet.h and bullet.cpp         # Bullets 
  ─ splitter.h and splitter.cpp     # Splitter bullet
  ─ powerup.h and powerup.cpp       # Power-ups and Bomb code
  ─ config.h                        # Game dimensions to avoid using in every file.
  ─ Makefile                        # Make files
  ─ README.md                       # Info about the game





- **Level progression**:
  - Level 1: Slower enemy spawns and shooting. 
  - Level 2: Achieved when score is 150 or above. Features Increased enemy activity. 
  - Level 3: Achieved when score is above 400. Medikits will not spawn anymore



- Language: C++17
- Platform: Unix-like systems i.e Mac and Linux
- Display: Terminal-based using ASCII characters
- Input: Keyboard input, arrow keys, spacebar, enter, q and esc
- Architecture: Object-oriented design with multiple structs for each object.


**Enjoy playing the gmae**
