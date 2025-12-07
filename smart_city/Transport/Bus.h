#pragma once
#include <string>
#include "PassengerQueue.h"
#include "BusRouteList.h"
#include "StopSimulator.h"
#include "RouteHistoryStack.h"

using namespace std;

class Bus {
public:
	string busNum;
	string companyName;
	int currentStop = 0;
	BusRouteList list;
	PassengerQueue queue;
	StopSimulator simulator;
	int numPassengers = 0;
	RouteHistoryStack stack;
	Bus(string n, string company) : busNum(n), companyName(company) {}

	void addStop(string stopID)
	{
		list.addStop(stopID);
		simulator.enqueue(stopID);
	}

	void addStop(BusStop* toAdd)
	{
		addStop(toAdd->stopId);
	}

	string* Simulate()
	{
		string* stopInfo = new string[2];

		stopInfo[0] = simulator.dequeue();

		if (stopInfo[0] != "")
		{
			simulator.enqueue(stopInfo[0]);
		}

		stopInfo[1] = simulator.peek();
		return stopInfo;
	}

	void loadPassengers(string* passengerNames, int count) {
		for (int i = 0; i < count; i++) {
			string passengerName = passengerNames[i];
			queue.enqueue(passengerName);
		}
	}

	void unloadPassengers(int numToUnload) {
		for (int i = 0; i < numToUnload; i++) {
			if (!queue.isEmpty()) {
				string name = queue.dequeue();
				cout << name << " has left the bus.\n";
			}
		}
	}
};
