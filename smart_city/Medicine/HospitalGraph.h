#pragma once
#include "HospitalEntities.h"

class HospitalEdge {
public:
    HospitalVertex* vertex;
    int weight;
    HospitalEdge* next;

    HospitalEdge(HospitalVertex* v, int w, HospitalEdge* n = nullptr)
        : vertex(v), weight(w), next(n) {
    }

    ~HospitalEdge() {}
};

class HospitalVertex {
public:
    int x;
    int y;
    Hospital hospital;
    HospitalEdge* adjList;

    HospitalVertex(int x_coord, int y_coord, const Hospital& h)
        : x(x_coord), y(y_coord), hospital(h), adjList(nullptr) {
    }

    ~HospitalVertex() {
        HospitalEdge* current = adjList;
        while (current != nullptr) {
            HospitalEdge* nextEdge = current->next;
            delete current;
            current = nextEdge;
        }
        adjList = nullptr;
    }
};

class HospitalGraph {
private:
    HospitalVertex* root;
    int count;

    void addHospital(int id, const char* name, float lat, float lon) {}
    void addEdge(int from, int to, int weight) {}
    void dijkstra(int start, int end) {}

public:
    HospitalGraph() : root(nullptr), count(0) {}

    ~HospitalGraph() {
        delete root;
    }
};