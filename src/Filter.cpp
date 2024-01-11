#include "Filter.h"

Filter::Filter(Map* map, unsigned int width, unsigned int height) {
    this->map = map;
    this->width = width;
    this->height = height;

    for(int i = 0; i <= map->getWidth() - width; i++) {
        for (int j = 0; j <= map->getHeight() - height; j++)
        {
            list<pair<int, int>> positionsWeed;

            if(i > 0 && j > 0) {
                getWeeds(&positionsWeed, i, j - 1, i + width, j);
                getWeeds(&positionsWeed, i - 1, j, i, j + height);
            } else if(i > 0) {
                getWeeds(&positionsWeed, i - 1, j, i, j + height);
            } if(j > 0) {
                getWeeds(&positionsWeed, i, j - 1, i + width, j);
            }

            if(positionsWeed.empty()) {
                getWeeds(&positionsWeed, i, j, i + width, j + height);

                if(positionsWeed.size() >= width * height) {
                    filteredWeeds.push_back({positionsWeed, {i + ((width - 1) / 2), j + ((height - 1) / 2)}});
                }
            }
        }
    }

    for(int i = 0; i < map->getWidth(); i++) {
        for (int j = 0; j < map->getHeight(); j++) {
            list<pair<int, int>> positionsBarrier;

            if(i > 0 && j > 0) {
                getBarriers(&positionsBarrier, i - 1, j);
                getBarriers(&positionsBarrier, i, j - 1);
            } else if(i > 0) {
                getBarriers(&positionsBarrier, i - 1, j);
            } if(j > 0) {
                getBarriers(&positionsBarrier, i, j - 1);
            }

            if(positionsBarrier.empty()) {
                getBarriers(&positionsBarrier, i, j);
                filteredBarriers.push_back(positionsBarrier);
            }
        }
    }
}

Filter::~Filter() {}

void Filter::getWeeds(list<pair<int, int>>* positions, int start_w, int start_h, int end_w, int end_h) {
    for (int k = start_w; k < end_w; k++)
    { 
        for (int l = start_h; l < end_h; l++)
        {
            if(map->getPositionValue({k, l}) != 1) {
                return;
            } else {
                positions->push_back({k, l});
            }
        }
    }

    if(end_w + 1 <= map->getWidth()) {
        getWeeds(positions, end_w, start_h, end_w + 1, end_h);
    }

    if(end_h + 1 <= map->getHeight()) {
        getWeeds(positions, start_w, end_h, end_w, end_h + 1);
    }
}

void Filter::getBarriers(list<pair<int, int>>* positions, int w, int h) {
    if(map->getPositionValue({w, h}) != 2) {
        return;
    } else {
        positions->push_back({w, h});
        
        if(w + 1 < map->getWidth()) {
            getBarriers(positions, w + 1, h);
        }

        if(h + 1 < map->getHeight()) {
            getBarriers(positions, w, h + 1);
        }
    }
}

Graph* Filter::makeGraph() {
    if(!filteredWeeds.empty()) {
        list<pair<int, int>> origin;
        origin.push_back({1, 1});

        Graph* graph = new Graph();
        
        graph->insertNode(origin, {1, 1});

        list<pair<list<pair<int, int>>, pair<int, int>>>::iterator it;
        for (it = filteredWeeds.begin(); it != filteredWeeds.end(); it++) {
            graph->insertNode((*it).first, (*it).second);
        }

        graph->interconnectAllNodes(filteredBarriers);
        
        return graph;
    } else {
        return nullptr;
    }
}