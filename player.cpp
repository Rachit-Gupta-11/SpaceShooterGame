#include "player.h"
#include <algorithm> 

Player::Player() : x(SCREEN_WIDTH / 2), symbol("/i\\"), switch_toFast(false),level(1), speed(1),score(0),nukes(3),lives(3) {}

void Player::toggle() {
    switch_toFast = !switch_toFast;
    if (switch_toFast)
    {
        speed = 5;
    }else{
        speed = 2;
    }


}

void Player::moveLeft() {
    x = std::max(0, x - speed);
}

void Player::moveRight() {
    int rightBoundary = SCREEN_WIDTH - symbol.length();
    x = std::min(rightBoundary, x + speed);
}