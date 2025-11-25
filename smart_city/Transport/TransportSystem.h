#pragma once
#include "BusStopGraph.h"
#include "BusHashTable.h"
#include "RouteHistoryStack.h"

class TransportSystem {
	BusStopGraph graph;
	BusHashTable busTable;
    RouteHistoryStack history;

	TransportSystem() {}

public:
    void registerCompany(string companyName) {}
    void registerBus(string busNo, string companyName, int stopId) {}
    void addBusStopInRoute(string busNo, int stopId) {}
    void addBusStop(string name, int stopId, float lat, float lon) {}
    void connectStops(int fromId, int toId, int distance) {}
    void shortestRoute(int startId, int endId) {}
    Bus* nearestBus(int stopId) {}
    Bus* searchBus(string busNum) {}

    void busSimulation(){}

    ~TransportSystem() {

    }

};