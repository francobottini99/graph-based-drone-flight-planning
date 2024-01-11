#include "Graph.h"

Graph::Graph() {
    first = nullptr;
    last = nullptr;
    size = 0;
    sizeEdge = 0;
}

Graph::~Graph() {
    Node* aux = last;

    while (aux != nullptr) {
        Node* del = aux;

        list<Edge*>::iterator it;
        for (it = aux->edges.begin(); it != aux->edges.end(); it++) {
            delete (*it)->destination;
        }     

        aux = aux ->previus;
        delete del; 
    }

    size = 0;
    first = nullptr;
    last = nullptr;
}

Node* Graph::getNode(pair<int, int> center) {
    Node* aux = first; 

    while (aux != nullptr) {
        if(center == aux->center) {
            return aux;
        }

        aux = aux->next;
    }

    return nullptr;
}

void Graph::insertNode(list<pair<int, int>> positions, pair<int, int> center) {
    if(getNode(center) == nullptr) {
        Node* aux = new Node(positions, center);

        if(first == nullptr) {
            first = aux;
            last = aux;
        } else {
            aux->previus = last;
            last->next = aux;
            last = aux;
        }

        size++;
    }
}

void Graph::insertEdge(Node* origin, Node* destination, int weight) {
    origin->edges.push_back(new Edge(destination, weight));
    destination->edges.push_back(new Edge(origin, weight));
    sizeEdge += 2;
}

void Graph::interconnectAllNodes(list<list<pair<int, int>>> barriers) {
    Node* head = first; 

    while (head != last) {
        Node* adjacent = head->next; 

        while (adjacent != nullptr) {
            bool add = true;

            list<list<pair<int, int>>>::iterator it;
            for (it = barriers.begin(); it != barriers.end(); it++) {
                pair<int, int> bStart;
                pair<int, int> bEnd;

                if((*it).front().first == (*it).back().first) {
                    bStart = {(*it).front().first, (*it).front().second - 1};
                    bEnd = {(*it).back().first, (*it).back().second + 1};
                } else {
                    bStart = {(*it).front().first - 1, (*it).front().second};
                    bEnd = {(*it).back().first + 1, (*it).back().second};
                }

                if(Map::doIntersect(head->getCenter(), adjacent->getCenter(), bStart, bEnd)) {
                    add = false;
                    break;  
                }
            }

            if(add) { 
                int distance = sqrt(pow(head->getCenter().first - adjacent->getCenter().first, 2) + pow(head->getCenter().second - adjacent->getCenter().second, 2));

                insertEdge(head, adjacent, distance);
            }

            adjacent = adjacent->next;
        }

        head = head->next;
    }
}

void Graph::print() {
    Node* aux = first; 

    while (aux != nullptr) {
        cout << "(" << aux->center.second << "; " << aux->center.first << ")" << " --> ";

        list<Edge*>::iterator it;
        for (it = aux->edges.begin(); it != aux->edges.end(); it++) {
            cout << "(" << (*it)->destination->center.second << "; " << (*it)->destination->center.first << ")" << " - ";
        }

        cout << endl << endl;
        aux = aux->next;
    }
}

list<pair<list<pair<int, int>>, pair<int, int>>> Graph::cycleHamiltonian(list<int>* distance) {
    list<pair<list<pair<int, int>>, pair<int, int>>> result;
    list<Edge*> invalid;
    list<Node*> path;
    list<Node*> visited;
    list<Edge*> trayect;
    Node* start = first;

    path.push_back(first);
    visited.push_back(first);
    distance->push_back(0);

    while((path.size() != size || !exist(path.back()->edges, first)) && invalid.size() < sizeEdge) {
        if(path.size() > 1) {
            path.pop_back();
            distance->pop_back();
            trayect.pop_back();
        }
        start = path.back();
        
        cycleHamiltonian(&path, &visited, &invalid, distance, &trayect, start);

        visited.remove(path.back());
        invalid.push_back(trayect.back());
    }

    if(path.size() > 1) {
        distance->push_back(weigth(path.back()->edges, first));
        path.push_back(first);

        list<Node*>::iterator it;
        for (it = path.begin(); it != path.end(); it++) {
            result.push_back({(*it)->positions, (*it)->center});
        }
    }

    return result;
}

void Graph::cycleHamiltonian(list<Node*>* path, list<Node*>* visited, list<Edge*>* invalid, list<int>* distance,  list<Edge*>* trayect, Node* n) {
    if(visited->size() == size) {
        return;
    } else {
        Edge* edge = nullptr;
        Node* next = nullptr;
        int minDistance = -1;
        
        list<Edge*>::iterator it;
        for (it = n->edges.begin(); it != n->edges.end(); it++) {
            if(!exist(*visited, (*it)->destination) && !exist(*invalid, *it)) {
                if((*it)->weight < minDistance || minDistance == -1) {
                    minDistance = (*it)->weight;
                    next = (*it)->destination;
                    edge = *it;
                }
            }
        }

        if(next != nullptr) {
            path->push_back(next);
            visited->push_back(next);
            distance->push_back(minDistance);
            trayect->push_back(edge);
            cycleHamiltonian(path, visited, invalid, distance, trayect, next);
        } else {
            return;
        }
    }
}

bool Graph::exist(list<Node*> l, Node* n) {
    list<Node*>::iterator it;
    for (it = l.begin(); it != l.end(); it++) {
        if(*it == n) {
            return true;
        }
    }

    return false;
}

bool Graph::exist(list<Edge*> l, Node* n) {
    list<Edge*>::iterator it;
    for (it = l.begin(); it != l.end(); it++) {
        if((*it)->destination == n) {
            return true;
        }
    }

    return false;
}

bool Graph::exist(list<Edge*> l, Edge* e) {
    list<Edge*>::iterator it;
    for (it = l.begin(); it != l.end(); it++) {
        if(*it == e) {
            return true;
        }
    }

    return false;
}

int Graph::weigth(list<Edge*> l, Node* n) {
    list<Edge*>::iterator it;
    for (it = l.begin(); it != l.end(); it++) {
        if((*it)->destination == n) {
            return (*it)->weight;
        }
    }

    return 0;
}