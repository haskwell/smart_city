#pragma once
#include "BusHashTable.h"
#include "RouteHistoryStack.h"

class TransportSystem {
	BusHashTable busTable;
    RouteHistoryStack history;

    void registerCompany(string companyName) {}
    void registerBus(string busNo, string companyName, int stopId) {}
    void addBusStopInRoute(string busNo, int stopId) {}
    void addBusStop(string name, int stopId, float lat, float lon) {}
    void connectStops(int fromId, int toId, int distance) {}
    void shortestRoute(int startId, int endId) {}
    Bus* nearestBus(int stopId) {}
    Bus* searchBus(string busNum) {}
    void addCompany(string name) {}

public:

    void registerCompanyHandler() {
        cout << ">>> Register Company - Not implemented yet\n\n";
    }

    void registerBusHandler() {
        cout << ">>> Register Bus with Route - Not implemented yet\n\n";
    }

    void addBusStopHandler() {
        cout << ">>> Add Bus Stop - Not implemented yet\n\n";
    }

    void connectStopsHandler() {
        cout << ">>> Connect Stops - Not implemented yet\n\n";
    }

    void busSimulation() {
        cout << ">>> Bus Simulation - Not implemented yet\n\n";
    }

    void shortestRouteHandler() {
        cout << ">>> Find Shortest Path - Not implemented yet\n\n";
    }

    void searchBusHandler() {
        cout << ">>> Get Bus Details - Not implemented yet\n\n";
    }

    ~TransportSystem() {

    }

};