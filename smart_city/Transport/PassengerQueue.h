#pragma once
#include <string>
using namespace std;
class PassengerQueue {
	string* names;
	int front;
	int rear;
	int count;
	int capacity;

public:
	PassengerQueue() : capacity(50), front(0), rear(-1), count(0) {
		names = new string[capacity];
		for (int i = 0; i < capacity; i++) {
			names[i] = "";
		}
	}
	bool isFull() {
		return count == capacity;
	}

	bool isEmpty() {
		return count == 0;
	}

	void enqueue() {

	}

	string dequeue() {
		return "";
	}

	~PassengerQueue() {

	}
};