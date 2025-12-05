#pragma once
#include "BusStop.h"
#include <string>
using namespace std;

class RouteNode {
public:
    string stopId;
    RouteNode* next;
    RouteNode(string id) : stopId(id), next(nullptr) {}
};

class BusRouteList {
public:
    RouteNode* head;

    BusRouteList() : head(nullptr) {}

    void addStop(BusStop* toAdd) {
        addStop(toAdd->stopId);
        return;
    }

    void addStop(string stopID) {
        RouteNode* newNode = new RouteNode(stopID);

        if (!head) {
            head = newNode;
            return;
        }

        RouteNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }


    ~BusRouteList() {
        RouteNode* curr = head;
        while (curr != nullptr) {
            RouteNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};