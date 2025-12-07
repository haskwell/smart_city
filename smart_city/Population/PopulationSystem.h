#pragma once
#include <string>
#include"../Database/database.h"
#include "../SmartCity/CityLogger.h"
using namespace std;

class PopulationSystem {
private:
    Database* db;
    CityLogger* logger;

    int addPerson(Person* p) {
        if (db->searchPerson(p->CNIC)) return 1;
        db->insertPerson(p);
        return 0;
    }

    Person* searchPersonByCNIC(const string& cnic) {
        return db->searchPerson(cnic);
    }

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

public:
    PopulationSystem(Database* database, CityLogger* log) : db(database), logger(log) {}
    void addPeopleHandler() {
        cls();
        logger->Title("ADD NEW PERSON");
        string name, CNIC, street, sector, occupation, specialization;
        int age, houseNo;
        char gender;

        logger->Prompt("Enter Name: ");
        getline(cin, name);
        logger->Prompt("Enter Age: ");
        cin >> age;
        logger->Prompt("Enter Gender (M/F): ");
        cin >> gender;
        cin.ignore();
        logger->Prompt("Enter CNIC: ");
        getline(cin, CNIC);
        logger->Prompt("Enter Street: ");
        getline(cin, street);
        logger->Prompt("Enter Sector: ");
        getline(cin, sector);
        logger->Prompt("Enter House Number: ");
        cin >> houseNo;
        cin.ignore();
        logger->Prompt("Enter Occupation: ");
        getline(cin, occupation);

        if (name == "" || CNIC == "" || street == "" || sector == "" || occupation == "" || houseNo <= 0) {
            logger->Warning("All fields must be filled correctly!");
            return pressEnterToContinue();
        }

        if (db->searchPerson(CNIC)) {
            logger->Warning("Person with CNIC '" + CNIC + "' already exists!");
            return pressEnterToContinue();
        }

        Person* newPerson = nullptr;
        if (occupation == "doctor" || occupation == "Doctor" || occupation == "DOCTOR") {
            logger->Prompt("Enter Doctor Specialization: ");
            getline(cin, specialization);
            newPerson = new Doctor(name, age, gender, CNIC, street, houseNo, occupation, sector, specialization);
            logger->Ok("Doctor '" + name + "' registered with specialization: " + specialization);
        }
        else if (occupation == "student" || occupation == "Student" || occupation == "STUDENT") {
            newPerson = new Student(name, age, gender, CNIC, street, houseNo, occupation);
            logger->Ok("Student '" + name + "' added to population.");
        }
        else if (occupation == "faculty" || occupation == "Faculty" || occupation == "FACULTY") {
            newPerson = new Faculty(name, age, gender, CNIC, street, houseNo, occupation);
            logger->Ok("Faculty '" + name + "' added to population.");
        }
        else {
            newPerson = new Person(name, age, gender, CNIC, street, houseNo, occupation, sector);
            logger->Ok("Person '" + name + "' added to population as '" + occupation + "'");
        }

        int code = addPerson(newPerson);
        if (code == 0) {}
        else if (code == 1) logger->Warning("Person already exists!");
        else logger->Error("Database missing!");
        pressEnterToContinue();
    }
    void searchByCNICHandler() {
        cls();
        logger->Title("SEARCH PERSON BY CNIC");
        string cnic;
        logger->Prompt("Enter CNIC to search: ");
        getline(cin, cnic);

        if (cnic == "") {
            logger->Warning("CNIC cannot be empty!");
            return pressEnterToContinue();
        }

        Person* person = searchPersonByCNIC(cnic);
        if (!person) {
            logger->Warning("No person found with CNIC: " + cnic);
            return pressEnterToContinue();
        }

        logger->Ok("Person Found!");
        logger->Info("Name        : " + person->name);
        logger->Info("CNIC        : " + person->CNIC);
        logger->Info("Age         : " + to_string(person->age));
        logger->Info("Gender      : " + string(1, person->gender));
        logger->Info("Occupation  : " + person->occupation);
        logger->Info("Address     : House #" + to_string(person->houseNo) + ", " + person->street + ", " + person->sector);

        if (person->occupation == "doctor" || person->occupation == "Doctor" || person->occupation == "DOCTOR") {
            Doctor* doc = dynamic_cast<Doctor*>(person);
            logger->Info("Specialization : " + doc->specialization);
        }
        pressEnterToContinue();
    }

    void generateAgeReport() {

        int oneToEighteen = 0;
        int nineteenTo25 = 0;
        int twentySixTo40 = 0;
        int fortyOneTo60 = 0;
        int sixtyOnePlus = 0;

        for (int i = 0; i < db->getPeopleTableSize(); i++) {
            PersonNode* current = db->getPersonAt(i);
            while (current) {
                int age = current->data->age;
                if (age >= 1 && age <= 18) oneToEighteen++;
                else if (age >= 19 && age <= 25) nineteenTo25++;
                else if (age >= 26 && age <= 40) twentySixTo40++;
                else if (age >= 41 && age <= 60) fortyOneTo60++;
                else if (age >= 61) sixtyOnePlus++;
                current = current->next;
            }
        }

        logger->Info("Population Age Report:");
        logger->Info("Age 1-18      : " + to_string(oneToEighteen));
        logger->Info("Age 19-25     : " + to_string(nineteenTo25));
        logger->Info("Age 26-40     : " + to_string(twentySixTo40));
        logger->Info("Age 41-60     : " + to_string(fortyOneTo60));
        logger->Info("Age 61+       : " + to_string(sixtyOnePlus));

    }

    void occupationSummaryReport() {


    }

    void genderRatioReport() {
        int maleCount = 0;
        int femaleCount = 0;

        for (int i = 0; i < db->getPeopleTableSize(); i++) {
            PersonNode* current = db->getPersonAt(i);
            while (current) {
                if (current->data->gender == 'M' || current->data->gender == 'm') {
                    maleCount++;
                }
                else if (current->data->gender == 'F' || current->data->gender == 'f') {
                    femaleCount++;
                }
                current = current->next;
            }

        }
        logger->Info("Gender Ratio Report");
        logger->Info("Men     : " + to_string(maleCount));
        logger->Info("Women   : " + to_string(femaleCount));

    }

    void generateReportHandler() {
        cls();
        generateAgeReport();
        logger->Info("\n");
        logger->Info("\n");
        logger->Info("\n");
        genderRatioReport();

        pressEnterToContinue();

    }

    void printHierarchyHandler() {
        cls();
        logger->Title("CITY HIERARCHY");

        if (!db->doSectorsExist()) {
            logger->Info("No sectors exist in the hierarchy.");
            pressEnterToContinue();
            return;
        }

        Sector* currSector = db->getCityHierarchySectors();

        while (currSector) {
            logger->Info("Sector: " + currSector->name);

            Street* currStreet = currSector->streets;
            if (!currStreet) {
                logger->Info("    (No streets in this sector)");
            }

            while (currStreet) {
                logger->Info("    Street: " + currStreet->name);

                House* currHouse = currStreet->houses;
                if (!currHouse) {
                    logger->Info("      (No houses on this street)");
                }

                while (currHouse) {
                    logger->Info("      House No: " + to_string(currHouse->houseNo));

                    Person* currPerson = currHouse->occupants;
                    if (!currPerson) {
                        logger->Info("        (No occupants in this house)");
                    }

                    while (currPerson) {
                        logger->Info("          Person: " + currPerson->name +
                            " | Age: " + to_string(currPerson->age) +
                            " | Gender: " + string(1, currPerson->gender) +
                            " | CNIC: " + currPerson->CNIC +
                            " | Occupation: " + currPerson->occupation);
                        currPerson = currPerson->next;
                    }

                    currHouse = currHouse->nextHouse;
                }

                currStreet = currStreet->nextStreet;
            }
            BuildingNode** buildings = currSector->buildings;
            logger->Info("    Buildings in Sector:");
            for (int i = 0; i < currSector->totalBuildings; i++) {
                BuildingNode* currBuilding = buildings[i];
                if (!currBuilding) {
                    logger->Info("      (No buildings of this type)");
                }
                else {
                    logger->Info("      " + to_string(i + 1) + ". " + currBuilding->type + "s:");
                    while (currBuilding) {
                        logger->Info("          ID: " + currBuilding->ID);
                        currBuilding = currBuilding->nextBuilding;
                    }
                }
            }
            currSector = currSector->nextSector;
            logger->Info("-------------------------------------------------");
        }

        pressEnterToContinue();
    }


    void searchHouseHandler() {
        logger->Title("SEARCH HOUSE");
        logger->Prompt("Enter Sector: ");
        string sectorName;
        getline(cin, sectorName);

        logger->Prompt("Enter Street: ");
        string streetName;
        getline(cin, streetName);

        logger->Prompt("Enter House Number: ");
        int houseNo;
        cin >> houseNo;
        cin.ignore();

        House* house = db->getHouse(sectorName, streetName, houseNo);
        if (!house) {
            logger->Warning("House not found");
            pressEnterToContinue();
            return;
        }

        logger->Ok("House found in city hierarchy");
        logger->Info("Sector name: " + sectorName);
        logger->Info("Street name: " + streetName);
        logger->Info("House number: " + to_string(houseNo));

        Person* currPerson = house->occupants;
        if (!currPerson) {
            logger->Info("    (No occupants in this house)");
        }
        else {
            while (currPerson) {
                logger->Info("    Name: " + currPerson->name);
                logger->Info("    Age: " + to_string(currPerson->age));
                logger->Info("    Gender: " + string(1, currPerson->gender));
                logger->Info("    CNIC: " + currPerson->CNIC);
                logger->Info("    Occupation: " + currPerson->occupation);
                logger->Info("----------------------");
                currPerson = currPerson->next;
            }
        }
        pressEnterToContinue();
    }


    void searchStreetHandler() {
        logger->Title("SEARCH STREET");
        logger->Prompt("Enter Sector Name: ");
        string sectorName;
        getline(cin, sectorName);

        Sector* sector = db->searchSector(sectorName);
        if (!sector) {
            logger->Warning("Sector '" + sectorName + "' not found.");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Street Name: ");
        string streetName;
        getline(cin, streetName);

        Street* street = sector->searchStreet(streetName);
        if (!street) {
            logger->Warning("Street '" + streetName + "' not found in sector '" + sectorName + "'.");
            pressEnterToContinue();
            return;
        }

        logger->Ok("Street found in sector");
        logger->Info("Street Name: " + street->name);

        House* currHouse = street->houses;
        if (!currHouse) {
            logger->Info("    (No houses in this street)");
        }
        else {
            while (currHouse) {
                logger->Info("    House No: " + to_string(currHouse->houseNo));
                Person* currPerson = currHouse->occupants;
                if (!currPerson) {
                    logger->Info("      (No occupants in this house)");
                }
                else {
                    while (currPerson) {
                        logger->Info("      Name: " + currPerson->name);
                        currPerson = currPerson->next;
                    }
                }
                currHouse = currHouse->nextHouse;
            }
        }
        pressEnterToContinue();
    }

    void searchSectorHandler() {
        logger->Title("SEARCH SECTOR");
        logger->Prompt("Enter Sector Name: ");
        string sectorName;
        getline(cin, sectorName);

        Sector* sector = db->searchSector(sectorName);
        if (!sector) {
            logger->Warning("Sector '" + sectorName + "' not found in the city hierarchy.");
            pressEnterToContinue();
            return;
        }

        logger->Ok("Sector '" + sectorName + "' found.");
        logger->Info("Sector Name: " + sector->name);

        Street* currStreet = sector->streets;
        if (!currStreet) {
            logger->Info("    (No streets in this sector)");
        }
        else {
            while (currStreet) {
                logger->Info("    Street: " + currStreet->name);
                House* currHouse = currStreet->houses;
                if (!currHouse) {
                    logger->Info("      (No houses in this street)");
                }
                else {
                    while (currHouse) {
                        logger->Info("      House No: " + to_string(currHouse->houseNo));
                        Person* currPerson = currHouse->occupants;
                        if (!currPerson) {
                            logger->Info("        (No occupants)");
                        }
                        else {
                            while (currPerson) {
                                logger->Info("          Name: " + currPerson->name);
                                currPerson = currPerson->next;
                            }
                        }
                        currHouse = currHouse->nextHouse;
                    }
                }
                currStreet = currStreet->nextStreet;
            }
        }
        pressEnterToContinue();
    }

    void printSectorGridHandler() {
        cls();
        logger->Title("SECTOR GRID");
        db->printSectorsInGrid();
        pressEnterToContinue();
    }

    void printBuildingsGridHandler() {
        cls();
        logger->Title("SECTOR BUILDINGS");
        string sectorName;
        logger->Prompt("Enter Sector Name: ");
        getline(cin, sectorName);
        Sector* sector = db->searchSector(sectorName);
        if (!sector) {
            logger->Warning("Sector '" + sectorName + "' not found.");
            pressEnterToContinue();
            return;
        }
        sector->printBuildingsGrid();
        pressEnterToContinue();
    }

    void drawPopulationHeatmap() {
        sf::RenderWindow window(sf::VideoMode(1000, 600), "City Population Heatmap");

        // Load font
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            // handle error
            return;
        }

        // Count max population first for color normalization
        int maxPopulation = 0;
        Sector* s = db->getCityHierarchySectors();
        while (s) {
            int total = 0;
            Street* street = s->streets;
            while (street) {
                House* house = street->houses;
                while (house) {
                    Person* p = house->occupants;
                    while (p) {
                        total++;
                        p = p->next;
                    }
                    house = house->nextHouse;
                }
                street = street->nextStreet;
            }
            if (total > maxPopulation) maxPopulation = total;
            s = s->nextSector;
        }

        auto getColorFromDensity = [](int count, int maxCount) {
            if (maxCount == 0) return sf::Color(255, 255, 204);
            int intensity = (count * 255) / maxCount;
            if (intensity > 255) intensity = 255;
            return sf::Color(intensity, 0, 0);
            };

        int sectorWidth = 150;
        int sectorHeight = 150;
        int margin = 20;
        int startX = 50;
        int startY = 50;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            int xOffset = 0;
            int yOffset = 0;
            int sectorsPerRow = 5; // adjust depending on window size

            s = db->getCityHierarchySectors();
            int idx = 0;
            while (s) {
                // Count total people in this sector
                int total = 0;
                Street* street = s->streets;
                while (street) {
                    House* house = street->houses;
                    while (house) {
                        Person* p = house->occupants;
                        while (p) {
                            total++;
                            p = p->next;
                        }
                        house = house->nextHouse;
                    }
                    street = street->nextStreet;
                }

                // Position
                xOffset = (idx % sectorsPerRow) * (sectorWidth + margin);
                yOffset = (idx / sectorsPerRow) * (sectorHeight + margin);

                // Draw rectangle
                sf::RectangleShape rect(sf::Vector2f(sectorWidth, sectorHeight));
                rect.setPosition(startX + xOffset, startY + yOffset);
                rect.setFillColor(getColorFromDensity(total, maxPopulation));
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(2);
                window.draw(rect);

                // Draw sector name
                sf::Text text(s->name, font, 14);
                text.setPosition(startX + xOffset + 5, startY + yOffset - 20);
                text.setFillColor(sf::Color::Black);
                window.draw(text);

                // Draw population count
                sf::Text popText(std::to_string(total), font, 16);
                popText.setPosition(startX + xOffset + 50, startY + yOffset + sectorHeight / 2 - 10);
                popText.setFillColor(sf::Color::Black);
                window.draw(popText);

                s = s->nextSector;
                idx++;
            }

            window.display();
        }
    }
};