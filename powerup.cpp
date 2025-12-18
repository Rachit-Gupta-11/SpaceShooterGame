#include "powerup.h"
#include <string>
#include <cstdlib>

medikit::medikit() : x(rand() % SCREEN_WIDTH), y(rand()%6), MedRep("M"),ticks(0), random(rand()){}

ExtraPoints::ExtraPoints() : x(rand() % SCREEN_WIDTH), y(rand()%6), PointsRep("+"),ticks(0), random(rand()){}

bomb::bomb(): x(rand()%SCREEN_WIDTH), y(rand()%6), BombRep("O"), ticks(0), random(rand()){}

void medikit::move(){   
    ticks++;
    if (ticks%5 == 0)
    {
        if (random%2==0)
        {
            x--;
        }else{
            x++;
        }
    }
}


void ExtraPoints::move(){   
    ticks++;
    if (ticks%5 == 0)
    {
        if (random%2==0)
        {
            x++;
        }else{
            x--;
        }
        
        
    }
}


void bomb::move(){
    ticks++;
    if(ticks%5 == 0){
        if (random%2==0)
        {
            x--;
        }else{
            x++;
        }
    }
}

