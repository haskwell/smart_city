#pragma once
#include "EducationEntities.h"

class SchoolEdge {
public:
    SchoolVertex* vertex;
    int weight;
    SchoolEdge* next;

    SchoolEdge(SchoolVertex* v, int w, SchoolEdge* n = nullptr)
        : vertex(v), weight(w), next(n) {
    }

    ~SchoolEdge() {}
};

class SchoolVertex {
public:
    int x;
    int y;
    School school;
    SchoolEdge* adjList;

    SchoolVertex(int x_coord, int y_coord, const School& s)
        : x(x_coord), y(y_coord), school(s), adjList(nullptr) {
    }

    ~SchoolVertex() {
        SchoolEdge* current = adjList;
        while (current != nullptr) {
            SchoolEdge* nextEdge = current->next;
            delete current;
            current = nextEdge;
        }
        adjList = nullptr;
    }
};

class SchoolGraph {
private:
    SchoolVertex* root;
    int count;

    void addStop(int id, const char* name, float lat, float lon) {}
    void addEdge(int from, int to, int weight) {}
    void dijkstra(int start, int end) {}

public:
    SchoolGraph() : root(nullptr), count(0) {}

    ~SchoolGraph() {
        delete root;
    }
};