#include "SmartCity/SmartCity.h"
#include <ctime>
#include <vector>
void seedTransport(SmartCity& city) {
    Database& db = *city.db;

    std::vector<std::string> sectors = { "S1","S2","S3","S4","S5" };
    int stopCounter = 1;

    for (int i = 0; i < sectors.size(); i++) {
        for (int j = 1; j <= 5; j++) {
            string sid = "BS" + to_string(stopCounter);
            string sname = "Stop " + to_string(stopCounter);
            float lat = 24.8600 + (stopCounter * 0.0005f);
            float lon = 67.0100 + (stopCounter * 0.0005f);

            db.insertBusStop(*new BusStop(sname, sid, sectors[i], lat, lon));
            stopCounter++;
        }
    }

    vector<string> companies = { "GreenLine", "MetroTrans", "RapidMove", "CityRide", "UrbanWheels" };
    for (auto& c : companies)
        db.insertBusCompany(*new BusCompany(c));

    int busNum = 1;
    for (auto& comp : companies)
        for (int i = 0; i < 4; i++)
            db.insertBusToCompany(comp, new Bus("B" + to_string(busNum++), comp));


    // Each bus gets a route of 5 stops
    int routeStart = 1;

    for (auto& comp : companies) {
        BusCompany* C = db.searchBusCompany(comp);

        if (!C) continue;

        for (int i = 0; i < C->busTable.tableSize; i++) {
            BusNode* busNode = C->busTable.table[i];
            while (busNode) {

                Bus* b = busNode->data;

                // Assign 5 stops sequentially
                for (int j = 0; j < 5; j++) {
                    string stopId = "BS" + to_string((routeStart + j - 1) % 25 + 1);
                    BusStop* s = db.searchBusStop(stopId);
                    if (s) b->addStop(s);
                }

                routeStart += 3; // Different route pattern per bus
                busNode = busNode->next;
            }
        }
    }
    db.makeEdges();
    cout << "\n[?] Transport System Seeded Successfully!\n";
}
#include <cstdlib> // for rand

void seedRandomHospital(SmartCity& city) {
    Database& db = *city.db;

    // Generate a new sector name that doesn't exist yet
    string newSector = "S" + to_string(db.getSectorsTableSize() + 1);

    // Create hospital with random name and ID
    string hospitalName = "Hospital";
    string hospitalID = "H1";
    int beds = 20 + (rand() % 31); // Random between 20-50 beds
    int specs = 3 + (rand() % 3);  // 3-5 specializations

    Hospital* h = new Hospital(hospitalName, hospitalID, beds, newSector, specs);

    // Optionally fill specializations with dummy values
    for (int i = 0; i < specs; i++) {
        h->specialization[i] = "Spec_" + to_string(i + 1);
    }

    // Insert the new sector (Database ensures it doesn't duplicate)
    db.ensureSectorExists(newSector);

    // Insert hospital into database
    db.insertHospital(*h);

    db.makeEdges();

    cout << "\n[?] Random Hospital '" << hospitalName << "' added in sector " << newSector << "!\n";
}


int main() {
	srand(static_cast<unsigned int>(time(0)));
	SmartCity city;
	seedTransport(city);
	seedRandomHospital(city);
    city.run();
    return 0;
}