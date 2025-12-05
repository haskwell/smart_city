#pragma once
#include <string>
#include "PassengerQueue.h"
#include "BusRouteList.h"
#include "StopSimulator.h"
using namespace std;

class Bus {
public:
	string busNum;

	string companyName;

	int currentStop;

	BusRouteList list;
	
	PassengerQueue queue;

	StopSimulator simulator;

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

};
