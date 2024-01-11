#include "Map.h"
#include "Graph.h"
#include "Filter.h"

void hidecursor();

int main() {
    for(int i = 0; i < 100; i++) {
        Map crops(100, 100);
        Filter weedDetector = Filter(&crops, 3, 3);
        Graph* weeds = weedDetector.makeGraph();
        list<int> distance;
        list<pair<list<pair<int, int>>, pair<int, int>>>  positions = weeds->cycleHamiltonian(&distance);

        if(!positions.empty()) {
            system("CLS");

            positions.pop_front();
            distance.pop_front();

            crops.print();
            crops.printData(positions);
            crops.printData(distance);

            list<pair<list<pair<int, int>>, pair<int, int>>>::iterator it;
            for (it = positions.begin(); it != positions.end(); it++) {
                crops.getDrone()->move((*it).second);
                crops.getDrone()->fumigate((*it).first);
            }
        }
    }

    cin.ignore();
    return 0;
}