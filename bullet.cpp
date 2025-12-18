#include "bullet.h"

Bullet::Bullet(int startX, int startY) : x(startX), y(startY), representation("|") {}

void Bullet::move() {
    y--;
}