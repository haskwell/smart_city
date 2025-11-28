#pragma once
#include "PassengerQueue.h"

class BusStop {
public:
	int stopId;
	string stopName;

	BusStop(int id, string name) : stopId(id), stopName(name) {}
};

class BusStopEdge {
public:
	BusStopVertex* to;
	int weight;

	BusStopEdge* next;

	BusStopEdge(BusStopVertex* t, int w) : to(t), weight(w), next(nullptr) {}
};

class BusStopVertex {
public:
	BusStop busStop;

	float lat;
	float lon;

	BusStopEdge* edgesList;
	BusStopVertex* next;

	PassengerQueue queue;

	BusStopVertex(string n, int id, float l, float o)
		: busStop(id, n),
		lat(l), lon(o),
		edgesList(nullptr), next(nullptr) {
	}

	~BusStopVertex() {
		BusStopEdge* current = edgesList;
		while (current != nullptr) {
			BusStopEdge* nextEdge = current->next;
			delete current;
			current = nextEdge;
		}
		edgesList = nullptr; // Defensive programming
	}
};

class BusStopGraph {
public:
	BusStopVertex* root;
	int count;

	BusStopGraph() : root(nullptr), count(0) {}

	void addStop(int id, string name, float lat, float lon) {}
	void addEdge(int from, int to, int weight) {}
	void dijkstra(int start, int end) {}

	~BusStopGraph() {
		BusStopVertex* current = root;
		while (current != nullptr) {
			BusStopVertex* nextStop = current->next;
			delete current;
			current = nextStop;
		}
		root = nullptr;
		count = 0;
	}
};