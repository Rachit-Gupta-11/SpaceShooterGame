#include "enemy.h"
#include <string>
#include <cstdlib> 

Enemy::Enemy() : representation("-V-") {
    x = rand() % SCREEN_WIDTH;
    y = rand()%6; 
}


EnemyBullet::EnemyBullet(int startX, int startY) : x(startX), y(startY), representation("'") {}


void EnemyBullet::move() {
    y++; 
}