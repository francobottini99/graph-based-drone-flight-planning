#ifndef __MAP_H__
#define __MAP_H__

#include <windows.h>
#include <WinUser.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <list>

#include "Drone.h"

using namespace std;

class Drone;

class Map
{
private:
    int** map;

    Drone* drone;

    unsigned int width;
    unsigned int height;
    unsigned int surface;

    void newMap(unsigned int width, unsigned int height);
    void randomMap();
    void cultivateMap();

    void configureConsole();

    list<pair<int, int>> getPositionsList();
public:
    Map(unsigned int width, unsigned int height);
    ~Map();

    static void gotoxy (pair<int, int> position);
    static int orientation(pair<int, int> p, pair<int, int> q, pair<int, int> r);
    static bool onSegment(pair<int, int> p, pair<int, int> q, pair<int, int> r);
    static bool doIntersect(pair<int, int> p1, pair<int, int> q1, pair<int, int> p2, pair<int, int> q2);
    void changeValue(pair<int, int> p);

    pair<int, int> getCursorPosition();

    int getWidth();
    int getHeight();
    int getPositionValue(pair<int, int> position);

    Drone* getDrone();

    void print();
    void printData(list<pair<list<pair<int, int>>, pair<int, int>>> positions);
    void printData(list<int> distance);
};

#endif