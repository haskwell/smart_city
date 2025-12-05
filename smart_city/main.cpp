#include "SmartCity/SmartCity.h"
#include <ctime>
#include <vector>
void seed(SmartCity& city) {
    Database& db = *city.db;

    vector<string> sectors = { "A", "B", "C", "D" };

    for (const string& sector : sectors) {
        for (int i = 1; i <= 5; i++) {
            Hospital hospital("H" + sector + to_string(i), "Hospital " + to_string(i), 50 + i * 5, sector, 3);
            db.insertHospital(hospital);
        }

        //db.printEntireGraph();

        for (int i = 1; i <= 5; i++) {
            Pharmacy pharmacy("P" + sector + to_string(i), "Pharmacy " + to_string(i), sector);
            db.insertPharmacy(pharmacy);
        }

        //db.printEntireGraph();

        for (int i = 1; i <= 5; i++) {
            School school("S" + sector + to_string(i), "School " + to_string(i), sector, 3.5 + (i % 2), 5);
            db.insertSchool(school);
        }

        //db.printEntireGraph();

        for (int i = 1; i <= 5; i++) {
            Mall mall("M" + sector + to_string(i), "Mall " + to_string(i), sector);
            db.insertMall(mall);
        }
        //db.printEntireGraph();
    }

    db.makeEdges();
}


int main() {
	srand(static_cast<unsigned int>(time(0)));
	SmartCity city;
	seed(city);
    city.run();
    return 0;
}