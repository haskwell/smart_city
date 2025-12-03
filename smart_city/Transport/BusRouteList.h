#pragma once
#include <string>
using namespace std;

class RouteNode {
public:
	string stopId;
	RouteNode* next;

	RouteNode(string id): stopId(id), next(nullptr) {}
};

class BusRouteList {
public:
    RouteNode* head;

    BusRouteList(): head(nullptr) {}

    void addStop(int stopID) {
        // implement later
    }

    ~BusRouteList() {

    }
};