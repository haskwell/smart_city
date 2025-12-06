#include "SmartCity/SmartCity.h"
#include <ctime>
#include <vector>
void seed(SmartCity& city) {
    Database& db = *city.db;

    // Create 25 sectors: S1, S2, ..., S25
    vector<string> sectors;
    for (int s = 1; s <= 25; s++) {
        sectors.push_back("S" + to_string(s));
    }

    for (const string& sector : sectors) {
        // 5 hospitals per sector
        for (int i = 1; i <= 5; i++) {
            Hospital hospital(
                "H" + sector + to_string(i),
                "Hospital " + to_string(i),
                50 + i * 5,
                sector,
                3
            );
            db.insertHospital(hospital);
        }

        // 5 pharmacies per sector
        for (int i = 1; i <= 5; i++) {
            Pharmacy pharmacy(
                "P" + sector + to_string(i),
                "Pharmacy " + to_string(i),
                sector
            );
            db.insertPharmacy(pharmacy);
        }

        // 5 schools per sector
        for (int i = 1; i <= 5; i++) {
            School school(
                "S" + sector + to_string(i),
                "School " + to_string(i),
                sector,
                3.5 + (i % 2),
                5
            );
            db.insertSchool(school);
        }

        // 5 malls per sector
        for (int i = 1; i <= 5; i++) {
            Mall mall(
                "M" + sector + to_string(i),
                "Mall " + to_string(i),
                sector
            );
            db.insertMall(mall);
        }

        // 5 facilities per sector
        for (int i = 1; i <= 5; i++) {
            Facility facility(
                "Facility",               // type
                "F" + sector + to_string(i), // id
                "Facility " + to_string(i),  // name
                sector                       // sector
            );
            db.insertFacility(facility);
        }


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