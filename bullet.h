#ifndef BULLET_H
#define BULLET_H

#include <string>

struct Bullet {
    int x, y;
    std::string representation;

    Bullet(int startX, int startY); 

    void move();
};

#endif 