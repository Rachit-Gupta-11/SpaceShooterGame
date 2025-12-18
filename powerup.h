#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include "config.h"


struct medikit{
    std::string MedRep;
    int random;
    int x,y;
    int ticks;
    medikit();
    // void job();
    void move();

};


struct ExtraPoints{
    std::string PointsRep;
    int random;
    int x,y;
    int ticks;
    ExtraPoints();
    void move();
};

struct bomb{
    std::string BombRep;
    int random;
    int x,y;
    int ticks;
    bomb();
    void move();
};




#endif