#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "config.h"

struct Enemy {
    int x, y;
    std::string representation;

    Enemy();
};

struct EnemyBullet {
    int x, y;
    std::string representation;

    EnemyBullet(int startX, int startY);

    void move();
};

#endif 