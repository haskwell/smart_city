#include "SmartCity/SmartCity.h"
#include <ctime>
#include <vector>
#include <tuple> // Added for std::tie
void seed(SmartCity& city) {
    Database& db = city.db;
    // Helper function to generate a random name
    auto generateName = [](int index) -> string {
        vector<string> firstNames = {
            "Alex", "Ben", "Chris", "Diana", "Emily", "Faisal", "Grace", "Henry",
            "Ivy", "Jack", "Kate", "Liam", "Mia", "Noah", "Olivia", "Peter", "Quinn",
            "Ryan", "Sophia", "Thomas", "Umair", "Victoria", "Will", "Xena", "Yara", "Zack"
        };
        vector<string> lastNames = {
            "Smith", "Jones", "Williams", "Brown", "Davis", "Miller", "Wilson", "Moore",
            "Taylor", "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Garcia"
        };
        string firstName = firstNames[rand() % firstNames.size()];
        string lastName = lastNames[rand() % lastNames.size()];
        return firstName + " " + lastName;
        };

    // Helper function to generate a random CNIC (13 digits)
    auto generateCNIC = [](int index) -> string {
        string cnic = "42"; // Starts with a common prefix
        for (int i = 0; i < 11; ++i) {
            cnic += to_string(rand() % 10);
        }
        return cnic;
        };

    // Helper function to generate a random address
    auto generateAddress = []() -> tuple<string, string, int> {
        vector<string> sectors = { "A", "B", "C", "D" };
        vector<string> streets = { "Main Street", "Oak Avenue", "Pine Lane", "Elm Road", "Maple Drive" };
        string sector = sectors[rand() % sectors.size()];
        string street = streets[rand() % streets.size()];
        int houseNo = 1 + rand() % 200; // House numbers from 1 to 200
        return { street, sector, houseNo };
        };

    // Helper function to generate a random specialization for doctors
    auto generateSpecialization = []() -> string {
        vector<string> specializations = { "Cardiology", "Neurology", "Pediatrics", "Oncology", "Dermatology", "General Practice" };
        return specializations[rand() % specializations.size()];
        };

    // Helper function to generate a random faculty subject
    auto generateSubject = []() -> string {
        vector<string> subjects = { "Computer Science", "Physics", "Chemistry", "Mathematics", "English", "History" };
        return subjects[rand() % subjects.size()];
        };

    // Helper function to generate a random age
    auto generateAge = [](const string& occupation) -> int {
        if (occupation == "student") {
            return 18 + rand() % 7; // 18-24
        }
        else if (occupation == "doctor" || occupation == "faculty") {
            return 28 + rand() % 23; // 28-50
        }
        else {
            return 20 + rand() % 40; // 20-59 for general occupations
        }
        };

    // Helper function to generate a random occupation (for the 50 random ones)
    auto generateRandomOccupation = []() -> string {
        vector<string> occupations = { "Engineer", "Architect", "Accountant", "Artist", "Journalist", "Chef", "Pilot", "Mechanic", "Retail Worker", "Librarian" };
        return occupations[rand() % occupations.size()];
        };

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

        float lat = 30.0f + static_cast<float>(rand() % 100) / 100.0f; 	// random-ish coords
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


    // -------------------------------
    // 4. SEED PEOPLE (100)
    // -------------------------------
    int personCount = 0;
    string name, CNIC, street, sector, occupation, specialization, subject;
    int age, houseNo;
    char gender;

    // --- 50 Random Occupations ---
    for (int i = 0; i < 50; i++) {
        personCount++;
        name = generateName(personCount);
        CNIC = generateCNIC(personCount);
        tie(street, sector, houseNo) = generateAddress();
        occupation = generateRandomOccupation();
        age = generateAge(occupation);
        gender = (rand() % 2 == 0) ? 'M' : 'F';

        Person* newPerson = new Person(name, age, gender, CNIC, street, houseNo, occupation, sector);
        db.people.insert(newPerson);
        city.population.cityHierarchy.addPerson(newPerson);
    }

    // --- 30 Students ---
    occupation = "student";
    for (int i = 0; i < 30; i++) {
        personCount++;
        name = generateName(personCount);
        CNIC = generateCNIC(personCount);
        tie(street, sector, houseNo) = generateAddress();
        age = generateAge(occupation);
        gender = (rand() % 2 == 0) ? 'M' : 'F';
        double gpa = 2.0 + static_cast<double>(rand() % 200) / 100.0; // GPA between 2.0 and 3.99

        Person* newPerson = new Student(name, age, gender, CNIC, street, houseNo, occupation, gpa);
        db.people.insert(newPerson);
        city.population.cityHierarchy.addPerson(newPerson);
    }

    // --- 10 Doctors ---
    occupation = "doctor";
    for (int i = 0; i < 10; i++) {
        personCount++;
        name = generateName(personCount);
        CNIC = generateCNIC(personCount);
        tie(street, sector, houseNo) = generateAddress();
        specialization = generateSpecialization();
        age = generateAge(occupation);
        gender = (rand() % 2 == 0) ? 'M' : 'F';

        Person* newPerson = new Doctor(name, age, gender, CNIC, street, houseNo, occupation, sector, specialization);
        db.people.insert(newPerson);
        city.population.cityHierarchy.addPerson(newPerson);
    }

    // --- 10 Faculty ---
    occupation = "faculty";
    for (int i = 0; i < 10; i++) {
        personCount++;
        name = generateName(personCount);
        CNIC = generateCNIC(personCount);
        tie(street, sector, houseNo) = generateAddress();
        subject = generateSubject();
        age = generateAge(occupation);
        gender = (rand() % 2 == 0) ? 'M' : 'F';

        Person* newPerson = new Faculty(name, age, gender, CNIC, street, houseNo, occupation, sector, subject);
        db.people.insert(newPerson);
        city.population.cityHierarchy.addPerson(newPerson);
    }

}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	SmartCity city;
	seed(city);
    city.run();
    return 0;
}