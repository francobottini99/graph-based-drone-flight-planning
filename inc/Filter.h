#ifndef __FILTER_H__
#define __FILTER_H__

#include "Map.h"
#include "Graph.h"

class Map;
class Graph;

class Filter
{
private:
    Map* map;

    list<pair<list<pair<int, int>>, pair<int, int>>> filteredWeeds;
    list<list<pair<int, int>>> filteredBarriers;

    unsigned int width;
    unsigned int height;
    
    void getWeeds(list<pair<int, int>>* positions, int start_w, int start_h, int end_w, int end_h);
    void getBarriers(list<pair<int, int>>* positions, int w, int h);
public:   
    Filter(Map* map, unsigned int width, unsigned int height);
    ~Filter();

    Graph* makeGraph();
};

#endif