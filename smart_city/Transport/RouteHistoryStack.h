#pragma once

class RouteStackNode {
public:
	int stopId;
	RouteStackNode* next;
	
	RouteStackNode(int id): stopId(id), next(nullptr) {}
};

class RouteHistoryStack {
	RouteStackNode* top;

public:
	RouteHistoryStack(): top(nullptr){}

	void push(int id) {

	}

	void clear() {

	}

	~RouteHistoryStack() {

	}
};