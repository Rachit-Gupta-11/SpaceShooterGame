#ifndef SPLITTER_H
#define SPLITTER_H

#include <string>

struct splitter {
    int x, y;
    std::string representation;
    int tick;

    splitter(int startX, int startY); 

    void move();

};

struct split{
    int x,y;
    std::string splitRepresentation;
    void hmovel();
    void hmover();
    split(int startX, int startY);

};


#endif 