#pragma once

class RouteNode {
public:
	int stopId;
	RouteNode* next;

	RouteNode(int id): stopId(id), next(nullptr) {}
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