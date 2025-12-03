#include "SmartCity/SmartCity.h"
#include <ctime>
#include <vector>

void seed(SmartCity& city) {
    Database& db = city.db;

    // -------------------------------
    // 1. SEED BUS COMPANIES (5)
    // -------------------------------
    vector<string> companies = {
        "MetroLine",
        "CityMove",
        "UrbanRide",
        "RapidTransit",
        "SkyBus"
    };

    for (auto& name : companies) {
        BusCompany* c = new BusCompany(name);
        db.busCompanies.insert(*c);
    }

    // -------------------------------
    // 2. SEED BUS STOPS (30)
    // -------------------------------
    for (int i = 1; i <= 30; i++) {
        string stopId = "S" + to_string(i);
        string name = "Stop " + to_string(i);

        float lat = 30.0f + static_cast<float>(rand() % 100) / 100.0f;   // random-ish coords
        float lon = 70.0f + static_cast<float>(rand() % 100) / 100.0f;

        BusStop* stop = new BusStop(name, stopId, lat, lon);
        db.busStops.insert(*stop);
    }

    // -------------------------------
    // 3. SEED BUSES (50)
    // Each company gets 10 buses
    // -------------------------------
    int busCounter = 1;

    for (auto& companyName : companies) {
        for (int i = 0; i < 10; i++) {
            string busNo = "B" + to_string(busCounter++);

            Bus* bus = new Bus(busNo, companyName);

            // Insert into that company's bus hash table
            db.busCompanies.insertBusToCompany(companyName, bus);
        }
    }

}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	SmartCity city;
	seed(city);
    city.run();
    return 0;
}