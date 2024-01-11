#ifndef __DRONE_H__
#define __DRONE_H__

#include "Map.h"
#include <iostream>

using namespace std;

class Map;

class Drone
{
private:
    Map* map;

    pair<int, int> position;
    pair<int, int> previusPosition;

    void clear();
    void move(char movement);

    bool colision;
public:
    Drone(Map* map);
    ~Drone();

    pair<int, int> getPosition();
    void move(pair<int, int> point);
    void fumigate(list<pair<int, int>> positions);
    void print();
};

#endif