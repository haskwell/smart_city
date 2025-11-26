#pragma once
#include "HospitalEntities.h"

class PharmacyEdge {
public:
    PharmacyVertex* vertex;
    int weight;
    PharmacyEdge* next;

    PharmacyEdge(PharmacyVertex* v, int w, PharmacyEdge* n = nullptr)
        : vertex(v), weight(w), next(n) {
    }

    ~PharmacyEdge() {}
};

class PharmacyVertex {
public:
    int x;
    int y;
    Pharmacy pharmacy;
    PharmacyEdge* adjList;

    PharmacyVertex(int x_coord, int y_coord, const Pharmacy& p)
        : x(x_coord), y(y_coord), pharmacy(p), adjList(nullptr) {
    }

    ~PharmacyVertex() {
        PharmacyEdge* current = adjList;
        while (current != nullptr) {
            PharmacyEdge* nextEdge = current->next;
            delete current;
            current = nextEdge;
        }
        adjList = nullptr;
    }
};

class PharmacyGraph {
private:
    PharmacyVertex* root;
    int count;

    void addStop(int id, const char* name, float lat, float lon) {}
    void addEdge(int from, int to, int weight) {}
    void dijkstra(int start, int end) {}

public:
    PharmacyGraph() : root(nullptr), count(0) {}

    ~PharmacyGraph() {
        delete root;
    }
};