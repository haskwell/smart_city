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
	PassengerQueue() : capacity(200), front(0), rear(-1), count(0) {
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

	void enqueue(string name) {
		if (isFull()) {
			return;
		}

		rear = (rear + 1) % capacity;
		names[rear] = name;
		count++;
	}

	string dequeue() {
		if (isEmpty()) {
			return "";
		}

		string value = names[front];
		names[front] = "";
		front = (front + 1) % capacity;
		count--;

		return value;
	}

	int getCount() {
		return count;
	}

	void print() {
		if (isEmpty()) {
			return;
		}

		int n = count;
		for (int i = 0; i < n; i++) {
			string passenger = dequeue();
			cout << passenger;
			cout << "\n";
			enqueue(passenger);
		}
		cout << "\n";
	}

	~PassengerQueue() {
		delete[]names;
	}
};