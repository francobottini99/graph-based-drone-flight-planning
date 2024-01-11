#include "Drone.h"

Drone::Drone(Map* map) {
    position = {1, 1};
    previusPosition = {1, 1};
    this->map = map;
}

Drone::~Drone() {} 

pair<int, int> Drone::getPosition() {
    return position;
}

void Drone::fumigate(list<pair<int, int>> positions) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    list<pair<int, int>>::iterator it;
    for (it = positions.begin(); it != positions.end(); it++) {
        map->changeValue(*it);

        if(position != *it) {
            map->gotoxy({(*it).first, (*it).second * 2});
            SetConsoleTextAttribute(hConsole, 10);
            cout << (unsigned char)219 << (unsigned char)219;
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
        
    Sleep(300);
}

void Drone::move(pair<int, int> point) {
    int dy = point.first - position.first;
    int dx = point.second - position.second;

    if(dy < 0) {
        if(dx < 0) {
            move('a');
        } else if(dx > 0) {
            move('c');
        } else {
            move('b');
        }
    } else if(dy > 0) {
        if(dx < 0) {
            move('g');
        } else if(dx > 0) {
            move('i');
        } else {
            move('h');
        }
    } else {
        if(dx < 0) {
            move('d');
        } else if(dx > 0) {
            move('f');
        } else {
            return;
        }
    }

    if(colision) {
        char mov[] = {'b', 'd', 'f', 'h'};
        move(mov[rand() % 4]);
    }

    Sleep(40);
    move(point);
}

void Drone::move(char movement) {
    previusPosition = position;

    switch (movement) {
    case 'a':
        if(position.first - 1 >= 0 && position.second - 1 >= 0) {
            if(map->getPositionValue({position.first - 1, position.second - 1}) != 2) {
                position.first--;
                position.second--;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;
    case 'b':
        if(position.first - 1 >= 0) {
            if(map->getPositionValue({position.first - 1, position.second}) != 2) {
                position.first--;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;
    case 'c':
        if(position.first - 1 >= 0 && position.second + 1 < map->getWidth()) {
            if(map->getPositionValue({position.first - 1, position.second + 1}) != 2) {
                position.first--;
                position.second++;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;
    case 'd':
        if(position.second - 1 >= 0) {
            if(map->getPositionValue({position.first, position.second - 1}) != 2) {
                position.second--;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;  
    case 'f':
        if(position.second + 1 < map->getWidth()) {
            if(map->getPositionValue({position.first, position.second + 1}) != 2) {
                position.second++;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;  
    case 'g':
        if(position.first + 1 < map->getHeight() && position.second - 1 >= 0) {
            if(map->getPositionValue({position.first + 1, position.second - 1}) != 2) {
                position.first++;
                position.second--;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;    
    case 'h':
        if(position.first + 1 < map->getHeight()) {
            if(map->getPositionValue({position.first + 1, position.second}) != 2) {
                position.first++;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;
    case 'i':
        if(position.first + 1 < map->getHeight() && position.second + 1 < map->getWidth()) {
            if(map->getPositionValue({position.first + 1, position.second + 1}) != 2) {
                position.first++;
                position.second++;
                colision = false;
            } else {
                colision = true;
            }
        }
        break;
    default:
        break;
    }

    clear();
    print();
}

void Drone::print() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    map->gotoxy({position.first, position.second * 2});
    
    SetConsoleTextAttribute(hConsole, 8);

    cout << (unsigned char)219 << (unsigned char)219;

    SetConsoleTextAttribute(hConsole, 15);
}

void Drone::clear() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    map->gotoxy({previusPosition.first, previusPosition.second * 2});
    
    if(map->getPositionValue(previusPosition) == 0) {
        SetConsoleTextAttribute(hConsole, 2);
    } else if(map->getPositionValue(previusPosition) == 1) {
        SetConsoleTextAttribute(hConsole, 14);
    } else if(map->getPositionValue(previusPosition) == 3) {
        SetConsoleTextAttribute(hConsole, 10);
    }

    cout << (unsigned char)219 << (unsigned char)219;

    SetConsoleTextAttribute(hConsole, 15);
}