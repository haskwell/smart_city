#pragma once
#include "PassengerQueue.h"
class Edge {
public:
	int to;
	int weight;

	Edge* next;

	Edge(int t, int w) : to(t), weight(w), next(nullptr) {}
};

class Vertex { //this is the bus stop
public:
	int stopId;
	string stopName;
	float lat;
	float lon;

	Edge* edgesList;
	Vertex* next;

	PassengerQueue queue;

	Vertex(string n, int id, float l, float o): stopName(n), lat(l), lon(o), edgesList(nullptr), next(nullptr), stopId(id) {}
};

class BusStopGraph {
public:
	Vertex* root;
	int count;

	BusStopGraph(): root(nullptr), count(0) {}

	void addStop(int id, const char* name, float lat, float lon) {}
	void addEdge(int from, int to, int weight) {}
	void dijkstra(int start, int end) {}

	~BusStopGraph() {

	}
};