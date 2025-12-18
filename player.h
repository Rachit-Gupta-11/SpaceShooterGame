#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "config.h" 

struct Player {
    int x;
    std::string symbol;
    bool switch_toFast;
    int level;
    int speed;
    int score;
    int nukes;
    int lives;
    Player();

    void toggle();
    void moveLeft();
    void moveRight();
};

#endif 