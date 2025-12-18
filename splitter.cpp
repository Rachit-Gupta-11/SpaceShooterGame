#include "splitter.h"

splitter::splitter(int startX, int startY) : x(startX), y(startY), representation("*"), tick(0){}
split::split(int startX, int startY) : x(startX), y(startY), splitRepresentation("-"){}

void splitter::move() {
    tick++;
    if(tick%2 == 0){
        y--;
    }
    
}

void split::hmovel(){
    x--;
}

void split::hmover(){
    x++;
}