#pragma once
#include <string>
using namespace std;

class RouteStackNode {
public:
	string stopId;
	RouteStackNode* next;
	
	RouteStackNode(string id): stopId(id), next(nullptr) {}
};

class RouteHistoryStack {
	RouteStackNode* top;

public:
	RouteHistoryStack(): top(nullptr){}

	void push(string id) {
		RouteStackNode* newNode = new RouteStackNode(id);
		newNode->next = top;
		top = newNode;
	}

	void clear() {
		while (top) {
			RouteStackNode* temp = top;
			top = top->next;
			delete temp;
		}
		top = nullptr;
	}

	void print() {
		if (!top) {
			std::cout << "Route history is empty.\n";
			return;
		}
		RouteStackNode* curr = top;
		std::cout << "Route History:\n";
		while (curr) {
			std::cout << "- " << curr->stopId << "\n";
			curr = curr->next;
		}
	}

	~RouteHistoryStack() {
		clear();
	}
};