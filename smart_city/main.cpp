#include "SmartCity/SmartCity.h"
#include <ctime>
#include <vector>
#include <string>
using namespace std;

//void seed(SmartCity& city) {
//    // Seed random number generator
//    srand(static_cast<unsigned int>(time(0)));
//
//    // 10 sample company names
//    std::vector<std::string> companyNames = {
//        "CityTrans", "MetroBus", "UrbanLine", "RapidRide", "EcoBus",
//        "TransitPro", "SwiftMove", "BlueRoute", "GreenLine", "ExpressWay"
//    };
//
//    // 10 sample bus stop names
//    std::vector<std::string> stopNames = {
//        "Central", "Parkside", "Hilltop", "Riverside", "EastEnd",
//        "WestGate", "NorthSquare", "SouthPoint", "OldTown", "NewCity"
//    };
//
//    // 1. Add bus companies
//    for (int i = 0; i < 10; i++) {
//        BusCompany* b = new BusCompany(companyNames[i]);
//        city.db->insertBusCompany(b);
//    }
//    // 3. Add bus stops
//    for (int i = 0; i < 10; i++) {
//        BusStop stop(stopNames[i], "S" + std::to_string(i + 1), "Sector" + std::to_string(i + 1));
//        city.db->insertBusStop(stop);
//    }
//    // 2. Add buses to random companies
//    for (int i = 0; i < 10; i++) {
//        std::string busNum = "B" + std::to_string(i + 1);
//        // Randomly pick a company
//        std::string company = companyNames[rand() % companyNames.size()];
//        Bus* bus = new Bus(busNum, company);
//        // Optionally, add stops to each bus
//        for (int j = 0; j < 3; j++) {
//            bus->addStop(stopNames[(i + j) % stopNames.size()]);
//        }
//        city.db->insertBusToCompany(company, bus);
//    }
//
//    // Optional: print confirmation
//    std::cout << "Seeded 10 companies, 10 buses, and 10 bus stops." << std::endl;
//
//    int numPeople = 500;
//    std::vector<std::string> firstNames = { "Alice","Bob","Charlie","Diana","Eve","Frank","Grace","Hank","Ivy","Jack" };
//    std::vector<std::string> lastNames = { "Smith","Johnson","Brown","Lee","Garcia","Martinez","Davis","Lopez","Wilson","Clark" };
//    std::vector<std::string> sectors = { "Sector1","Sector2","Sector3","Sector4","Sector5" };
//
//    for (int i = 0; i < numPeople; i++) {
//        std::string name = firstNames[city.db->randomNumber() % firstNames.size()] + " " +
//            lastNames[city.db->randomNumber() % lastNames.size()];
//        int age = 10 + city.db->randomNumber() % 60; // age 10–69
//        char gender = (city.db->randomNumber() % 2 == 0) ? 'M' : 'F';
//        std::string cnic = std::to_string(100000000000 + city.db->randomNumber() % 900000000000);
//        std::string street = "Street" + std::to_string(city.db->randomNumber() % 50 + 1);
//        int houseNo = 1 + city.db->randomNumber() % 100;
//        std::string occupation = "Occupation" + std::to_string(city.db->randomNumber() % 20 + 1);
//        std::string sector = sectors[city.db->randomNumber() % sectors.size()];
//
//        Person* p = new Person(name, age, gender, cnic, street, houseNo, occupation, sector);
//        city.db->insertPerson(p);
//    }
//
//}

int main() {
    SmartCity city;
    //seed(city);
    city.run();
    return 0;
}
