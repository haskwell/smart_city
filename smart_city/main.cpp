#include "SmartCity/SmartCity.h"
#include <ctime>
#include <vector>
void seed(SmartCity& city) {
    Database& db = *city.db;

    // Define 5 sectors
    vector<string> sectors = { "S1", "S2", "S3", "S4", "S5" };

    for (int i = 0; i < sectors.size(); i++) {
        const string& sector = sectors[i];

        switch (i) {
        case 0: // Sector S1: Hospitals
            for (int j = 1; j <= 5; j++) {
                Hospital hospital(
                    "H" + sector + to_string(j),
                    "Hospital " + to_string(j),
                    50 + j * 5,
                    sector,
                    3
                );
                db.insertHospital(hospital);
            }
            break;

        case 1: // Sector S2: Pharmacies
            for (int j = 1; j <= 5; j++) {
                Pharmacy pharmacy(
                    "P" + sector + to_string(j),
                    "Pharmacy " + to_string(j),
                    sector
                );
                db.insertPharmacy(pharmacy);
            }
            break;

        case 2: // Sector S3: Schools
            for (int j = 1; j <= 5; j++) {
                School school(
                    "Sch" + sector + to_string(j),
                    "School " + to_string(j),
                    sector,
                    3.5 + (j % 2),
                    5
                );
                db.insertSchool(school);
            }
            break;

        case 3: // Sector S4: Malls
            for (int j = 1; j <= 5; j++) {
                Mall mall(
                    "M" + sector + to_string(j),
                    "Mall " + to_string(j),
                    sector
                );
                db.insertMall(mall);
            }
            break;

        case 4: // Sector S5: Facilities
            for (int j = 1; j <= 5; j++) {
                Facility facility(
                    "Facility",
                    "F" + sector + to_string(j),
                    "Facility " + to_string(j),
                    sector
                );
                db.insertFacility(facility);
            }
            break;
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