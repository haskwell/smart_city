#pragma once
#pragma once
#include "MallEntities.h"

class MallEdge {
public:
    MallVertex* vertex;
    int weight;
    MallEdge* next;

    MallEdge(MallVertex* v, int w, MallEdge* n = nullptr)
        : vertex(v), weight(w), next(n) {
    }

    ~MallEdge() {}
};

class MallVertex {
public:
    int x;
    int y;
    Mall mall;
    MallEdge* adjList;

    MallVertex(int x_coord, int y_coord, const Mall& m)
        : x(x_coord), y(y_coord), mall(m), adjList(nullptr) {
    }

    ~MallVertex() {
        MallEdge* current = adjList;
        while (current != nullptr) {
            MallEdge* nextEdge = current->next;
            delete current;
            current = nextEdge;
        }
        adjList = nullptr;
    }
};

class MallGraph {
private:
    MallVertex* root;
    int count;

    void addMall(int id, const char* name, float lat, float lon) {}
    void addEdge(int from, int to, int weight) {}
    void dijkstra(int start, int end) {}

public:
    MallGraph() : root(nullptr), count(0) {}

    ~MallGraph() {
        delete root;
    }
};