#pragma once
#include <string>
#include "BusStop.h"
using namespace std;


class StopSimNode {
public:
    string stopId;
    StopSimNode* next;

    StopSimNode(string id) : stopId(id), next(nullptr) {}
};

class StopSimulator {
private:
    StopSimNode* front;
    StopSimNode* rear;

public:
    StopSimulator() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(BusStop* toAdd)
    {
        if (!toAdd)
        {
            return;
        }
        
        enqueue(toAdd->stopId);
        return;
    }
    void enqueue(string stopId) {
        StopSimNode* newNode = new StopSimNode(stopId);

        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    string dequeue() {
        if (isEmpty())
        {
            return "";
        }

        StopSimNode* temp = front;
        string removed = temp->stopId;

        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
        return removed;
    }

    string peek()
    {
        if (isEmpty())
        {
            return "";
        }
        return front->stopId;
    }
};
