#include "Map.h"

Map::Map(unsigned int width, unsigned int height) {
    if(width >= 10 && height >= 10) {
        drone = new Drone(this);
        newMap(width, height);
        randomMap();
        configureConsole();
    }
}

void Map::changeValue(pair<int, int> p) {
    map[p.first][p.second] = 3;
}

Map::~Map() {
    for (int i = 0; i < height; i++)
    {
        delete [] map[i];
    }
    
    delete [] map;
    delete drone;
}

void Map::newMap(unsigned int width, unsigned int height) {
    this->width = width; 
    this->height = height;
    surface = width * height;

    map = new int* [height];
    for (int i = 0; i < height; i++)
    {
        map[i] = new int[width];
    }

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            map[i][j] = -1;
        }
    }
}

void Map::cultivateMap() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            map[i][j] = 0;
        }
    }  
}


list<pair<int, int>> Map::getPositionsList() {
    list<pair<int, int>> positions;

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            positions.push_back({i, j});
        }
    }

    return positions;
}

void Map::randomMap() {
    cultivateMap();

    srand(time(NULL));

    int undergrowth = rand() % (int)pow(log10(surface), 3) + (int)pow(log10(surface), 2);
    int barriers = rand() % (int)pow(log10(surface), 2) + (int)log10(surface);

    list<pair<int, int>> auxUndergrowthList = getPositionsList();
    list<pair<int, int>> auxBarrierList = auxUndergrowthList;

    for (int i = 0; i < undergrowth; i++) {
        int count = 0;
        int position = rand() % auxUndergrowthList.size();
        pair<int, int> start;

        list <pair<int, int>> :: iterator it;
        for(it = auxUndergrowthList.begin(); it != auxUndergrowthList.end(); ++it) {
            if(count == position) {
                start = *it;
                break;
            } 

            count++;
        }

        int size_x, size_y;
        bool end;
        count = 0;

        do {
            end = true;

            size_x = rand() % (int)(2 * log10(surface)) + 1;
            size_y = rand() % (int)(2 * log10(surface)) + 1;

            if(size_x + start.first <= width && size_y + start.second <= height){
                int limit_x = (start.first + size_x + 1 < width)? start.first + size_x + 1: start.first + size_x;
                int limit_y = (start.second + size_y + 1 < height)? start.second + size_y + 1 : start.second + size_y;
                int start_x = (start.first - 1 < width)? start.first - 1 : start.first;
                int start_y = (start.second - 1 < height)? start.second - 1 : start.second;

                for (int j = start_x; j < limit_x; j++) {
                    for (int k = start_y; k < limit_y; k++) {
                        if(map[j][k] != 0) {
                            end = false;
                        }
                    }
                }
            } else {
                end = false;
            }

            if(end) {
                for (int j = start.first; j < start.first + size_x; j++) {   
                    for (int k = start.second; k < start.second + size_y; k++) {
                        auxBarrierList.remove({j, k});
                        auxUndergrowthList.remove({j, k});
                        auxUndergrowthList.remove({j - 1, k});
                        auxUndergrowthList.remove({j + 1, k});
                        auxUndergrowthList.remove({j, k - 1});
                        auxUndergrowthList.remove({j, k + 1});

                        map[j][k] = 1;
                    }
                }    
            }

            count++;
        } while (!end && count < 100);  
    }

    for(int i = 0; i < barriers; i++) {
        int count = 0;
        int position = rand() % auxBarrierList.size();
        pair<int, int> start;

        list <pair<int, int>> :: iterator it;
        for(it = auxBarrierList.begin(); it != auxBarrierList.end(); ++it) {
            if(count == position) {
                start = *it;
                break;
            } 

            count++;
        }

        int size_x, size_y, orientation;
        bool end;
        count = 0;

        do {
            end = true;

            orientation = rand() % 2;

            if(orientation == 0) {
                size_x = rand() % (int)(2 * log10(surface)) + 4;
                size_y = 1;
            } else {
                size_x = 1;
                size_y = rand() % (int)(2 * log10(surface)) + 4;
            }

            if(size_x + start.first <= width && size_y + start.second <= height){
                int limit_x = (start.first + size_x + 1 < width)? start.first + size_x + 1: start.first + size_x;
                int limit_y = (start.second + size_y + 1 < height)? start.second + size_y + 1 : start.second + size_y;
                int start_x = (start.first - 1 < width)? start.first - 1 : start.first;
                int start_y = (start.second - 1 < height)? start.second - 1 : start.second;

                for (int j = start_x; j < limit_x; j++) {
                    for (int k = start_y; k < limit_y; k++) {
                        if(map[j][k] != 0) {
                            if(map[j][k] == 1) {
                                if(j != start.first + size_x + 1 && j != start.first - 1 && k != start.second + size_y + 1 && k != start.second - 1) {
                                    end = false;
                                }
                            } else {
                                end = false;
                            }
                        }
                    }
                }
            } else {
                end = false;
            }

            if(end) {
                for (int j = start.first; j < start.first + size_x; j++) {   
                    for (int k = start.second; k < start.second + size_y; k++) {
                        auxBarrierList.remove({j, k});
                        auxBarrierList.remove({j - 1, k});
                        auxBarrierList.remove({j + 1, k});
                        auxBarrierList.remove({j, k - 1});
                        auxBarrierList.remove({j, k + 1});

                        map[j][k] = 2;
                    }
                }    
            }

            count++;
        } while (!end && count < 100);  

    }
}

int Map::getWidth() {
    return width;
}

int Map::getHeight() {
    return height;
}

int Map::getPositionValue(pair<int, int> position) {
    return map[position.first][position.second];
}

Drone* Map::getDrone() {
    return drone;
}

void Map::printData(list<pair<list<pair<int, int>>, pair<int, int>>> positions) {
    int count = 0;
    list<pair<list<pair<int, int>>, pair<int, int>>>::iterator it;
    for (it = positions.begin(); it != positions.end(); it++) {
        gotoxy({count, width * 2 + 10});
        cout << "(" << (*it).second.second << "; " << (*it).second.first << ")";
        count++;
    }
}

void Map::printData(list<int> distance) {
    int count = 0;
    int total = 0;
    list<int>::iterator it;
    for (it = distance.begin(); it != distance.end(); it++) {
        gotoxy({count, width * 2 + 30});
        total += *it;
        cout << total;
        count++;
    }
}

void Map::print() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    gotoxy({0, 0});

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if(map[i][j] == 0) {
                SetConsoleTextAttribute(hConsole, 2);
            } else if(map[i][j] == 1) {
                SetConsoleTextAttribute(hConsole, 14);
            } else if(map[i][j] == 2) {
                SetConsoleTextAttribute(hConsole, 4);
            } else if(map[i][j] == 3) {
                SetConsoleTextAttribute(hConsole, 10);
            } else {
                SetConsoleTextAttribute(hConsole, 15);
            }

            cout << (unsigned char)219 << (unsigned char)219;
        }

        cout << endl;
    }

    drone->print();
    SetConsoleTextAttribute(hConsole, 15);
}

int Map::orientation(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
    int val = (q.first - p.first) * (r.second - q.second) -
              (q.second - p.second) * (r.first - q.first);
  
    if (val == 0) return 0;
  
    return (val > 0)? 1: 2;
}

bool Map::onSegment(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
    if (q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second) &&
        q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first))
       return true;
  
    return false;
}

bool Map::doIntersect(pair<int, int> p1, pair<int, int> q1, pair<int, int> p2, pair<int, int> q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
  
    if (o1 != o2 && o3 != o4)
        return true;
  
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
  
    return false;
}

void Map::gotoxy (pair<int, int> position) {
    HANDLE hcon;
    hcon = GetStdHandle ( STD_OUTPUT_HANDLE );
    COORD dwPos;
    dwPos.X = position.second;
    dwPos.Y = position.first;
    SetConsoleCursorPosition ( hcon, dwPos );
}

pair<int, int> Map::getCursorPosition() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi = { };
    BOOL ok = GetConsoleScreenBufferInfo (hConsole, &csbi);
    return {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
}

void Map::configureConsole() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}