#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "Map.h"
#include <math.h> 
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Node;

class Edge {
private:
    Edge(Node* destination, int weight) {
        this->weight = weight;
        this->destination = destination;
    }

    int weight;
    Node* destination;

    friend class Graph;
};

class Node {
private:
    Node(list<pair<int, int>> positions, pair<int, int> center) {
        this->positions = positions;
        this->center = center;
        previus = nullptr;
        next = nullptr;
    };

    Node* next;
    Node* previus;

    list<struct Edge*> edges;
    list<pair<int, int>> positions;
    pair<int, int> center;
public:
    pair<int, int> getCenter() { return center; };

    friend class Graph;
};

class Graph
{
private:      
    int size;
    int sizeEdge;

    Node* first;
    Node* last;

    Node* getNode(pair<int, int> center);
    bool exist(list<Node*> l, Node* n);
    bool exist(list<Edge*> l, Node* n);
    bool exist(list<Edge*> l, Edge* e);
    int weigth(list<Edge*> l, Node* n);
    void insertEdge(Node* origin, Node* destination, int weight);
    void cycleHamiltonian(list<Node*>* path, list<Node*>* visited, list<Edge*>* invalid, list<int>* distance, list<Edge*>* trayect, Node* n);
public:
    Graph();
    ~Graph();

    void insertNode(list<pair<int, int>> positions, pair<int, int> center);
    void interconnectAllNodes(list<list<pair<int, int>>> barriers);
    void print();

    list<pair<list<pair<int, int>>, pair<int, int>>> cycleHamiltonian(list<int>* distance);
    
};

#endif