class PublicSystem {
    Database* db;
    CityLogger* logger;

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

    int registerFacilityCore(Facility* facility) {
        if (db->searchFacility(facility->id)) {
            delete facility;
            return 1;
        }
        db->insertFacility(*facility);
        return 0;
    }

public:
    PublicSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}
    void addFacilityHandler() {
        cls();
        logger->Title("REGISTER NEW FACILITY");
        string id, name, type, sector;
        logger->Prompt("Enter Facility ID: ");
        cin >> id;
        cin.ignore();
        logger->Prompt("Enter Facility Name: ");
        getline(cin, name);
        logger->Prompt("Enter Facility Type (e.g., Park, Power Plant): ");
        getline(cin, type);
        logger->Prompt("Enter Facility Sector: ");
        getline(cin, sector);
        if (id == "" || name == "" || type == "" || sector == "") {
            logger->Warning("All fields must be filled! Registration cancelled.");
            pressEnterToContinue();
            return;
        }
        Facility* newFacility = new Facility(id, name, type, sector);
        int code = registerFacilityCore(newFacility);
        if (code == 0) logger->Ok("Facility '" + name + "' has been registered successfully.");
        else if (code == 1) logger->Warning("Facility with ID '" + id + "' already exists!");
        else logger->Error("Database missing. Cannot register facility.");
        pressEnterToContinue();
    }

    void listAllFacility() {
        cls();
        logger->Title("LIST OF ALL PUBLIC FACILITIES");
        if (db->getFacilityTableSize() == 0) {
            logger->Warning("No facilities registered yet.");
            pressEnterToContinue();
            return;
        }
        for (int i = 0; i < db->getFacilityTableSize(); i++) {
            FacilityNode* current = db->getFacilityAt(i);
            while (current) {
                logger->Info("ID: " + current->data.id + " | Name: " + current->data.name + " | Type: " + current->data.type);
                current = current->next;
            }
        }
        cout << endl;
        pressEnterToContinue();
    }

    void findNearestUtilityHandler() {
        cls();
        logger->Title("FIND SHORTEST PATH TO FACILITY");
        string startID;
        logger->Prompt("Enter Start Node ID: ");
        getline(cin, startID);
        string targetType = db->getFacilityTag();
        if (startID == "") {
            logger->Warning("Empty field!");
            pressEnterToContinue();
            return;
        }
        string path = db->findPathByType(startID, targetType);
        if (path == "") {
            logger->Warning("No path found.");
        }
        else {
            logger->Info("Shortest Path: " + path);
        }
        logger->Info(path);
        pressEnterToContinue();
    }
};