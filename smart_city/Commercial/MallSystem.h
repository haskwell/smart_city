#pragma once
#include <iostream>
#include"../Database/Database.h"
#include "../SmartCity/CityLogger.h"
#include"MallEntities.h"

using namespace std;

class MallSystem {
private:
    Database* db;
    CityLogger* logger;

    void pressEnterToContinue() {
        logger->Prompt("Press Enter to continue...");
        cin.ignore(); // Wait for user input
        cin.get();    // Catch the actual enter key
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

public:
    MallSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}

    // Converted to int and REMOVED DB NULLPTR CHECK
    // Returns 1 for Success, 0 for Failure
    int addMall(Mall* mall)
    {
        // Removed if (!db) check as requested

        if (db->searchMall(mall->mallId))
        {
            logger->Warning("Mall with ID '" + mall->mallId + "' already exists!");
            delete mall;
            return 0; // Failure
        }

        db->insertMall(*mall);
        return 1; // Success
    }

    // ADDED INPUT VALIDATION
    void registerMallsHandler() {
        cls();
        logger->Title("REGISTER NEW MALL");

        string mallID, name, sector;

        logger->Prompt("Enter Mall ID: ");
        cin >> mallID;
        cin.ignore(); // Clear buffer

        logger->Prompt("Enter Mall Name: ");
        getline(cin, name);

        logger->Prompt("Enter Mall Sector: ");
        getline(cin, sector);

        // Input Validation
        if (mallID.empty() || name.empty() || sector.empty()) {
            logger->Error("Invalid Input: All fields (ID, Name, Sector) are required.");
            pressEnterToContinue();
            return;
        }

        Mall* newMall = new Mall(mallID, name, sector);

        // Using the int return (1 is true-ish in C++)
        if (addMall(newMall))
        {
            logger->Ok("Mall " + name + " has been registered.");
        }
        else
        {
            logger->Error("Registration Failed.");
        }

        pressEnterToContinue();
    }

    // Converted to int and REMOVED DB NULLPTR CHECK
    // Returns 1 for Success, 0 for Failure
    int addProduct(Product product, Mall* mall) {
        // Removed if (db == nullptr || mall == nullptr) check as requested

        if (mall->productTable.search(product.name)) {
            logger->Warning("Product with name '" + product.name + "' already exists in mall '" + mall->name + "'!");
            return 0; // Failure
        }

        mall->productTable.insert(product);
        logger->Ok("Product " + product.name + " added to Mall " + mall->name + ".");

        return 1; // Success
    }

    // Converted to int and REMOVED DB NULLPTR CHECK
    int addItemsHandler() {
        cls();
        logger->Title("ADD ITEM TO MALL");
        string mallID;

        logger->Prompt("Enter Mall ID: ");
        cin >> mallID;
        cin.ignore();

        // Validating Mall ID input
        if (mallID.empty()) {
            logger->Error("Invalid Input: Mall ID cannot be empty.");
            pressEnterToContinue();
            return 0;
        }

        Mall* mall = db->searchMall(mallID);

        if (mall == nullptr)
        {
            logger->Error("Mall with ID '" + mallID + "' not found!");
            pressEnterToContinue();
            return 0;
        }

        int count;
        logger->Prompt("Enter number of items to add: ");
        cin >> count;

        // Input Validation for Count
        if (cin.fail() || count <= 0) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            logger->Error("Invalid Input: Please enter a valid positive number.");
            pressEnterToContinue();
            return 0;
        }
        cin.ignore();

        for (int i = 0; i < count; i++)
        {
            string name, category;
            float price;

            logger->Info("------Product " + to_string(i + 1) + " Details------");

            logger->Prompt("Enter Product Name: ");
            getline(cin, name);
            if (name.empty()) {
                logger->Warning("Name cannot be empty. Skipping item.");
                continue;
            }

            logger->Prompt("Enter Product Category: ");
            getline(cin, category);
            if (category.empty()) {
                logger->Warning("Category cannot be empty. Skipping item.");
                continue;
            }

            logger->Prompt("Enter Product Price: ");
            cin >> price;

            // Input Validation for Price
            if (cin.fail() || price < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                logger->Error("Invalid Price. Skipping item.");
                continue;
            }
            cin.ignore();

            Product p(name, price, category);
            addProduct(p, mall);
        }

        pressEnterToContinue();
        return 1; // Success
    }

    // ADDED INPUT VALIDATION
    void itemSearchHandler() {
        cls();
        logger->Title("SEARCH ITEM (CATEGORY BASED)");

        string mallID, category;

        logger->Prompt("Enter Mall ID to seach in: ");
        cin >> mallID;
        cin.ignore();

        if (mallID.empty()) {
            logger->Error("Input Error: Mall ID is required.");
            pressEnterToContinue();
            return;
        }

        Mall* mall = db->searchMall(mallID);

        if (mall == nullptr)
        {
            logger->Error("Mall with ID " + mallID + " not found.");
            pressEnterToContinue();
            return;
        }

        if (mall->productTable.tableSize == 0)
        {
            logger->Warning("No products found in Mall " + mall->name + ".");
            pressEnterToContinue();
            return;
        }

        logger->Prompt("Enter Product Category to search: ");
        getline(cin, category);

        if (category.empty()) {
            logger->Error("Input Error: Category is required.");
            pressEnterToContinue();
            return;
        }

        logger->Info("Products in category '" + category + "' in Mall '" + mall->name + "':");

        bool found = false;

        for (int i = 0; i < mall->productTable.tableSize; i++)
        {
            ProductNode* current = mall->productTable.table[i];
            while (current)
            {
                if (current->data.category == category)
                {
                    logger->Info(" - " + current->data.name + " | Price: " + to_string(current->data.price));
                    found = true;
                }
                current = current->next;
            }
        }

        if (found == false)
        {
            logger->Warning("No products found in category '" + category + "' in Mall '" + mall->name + "'.");
        }

        pressEnterToContinue();
    }

    void findNearestMallHandler() {
        cls();
        logger->Title("NEAREST MALL LOOKUP");
        logger->Info(">>> Nearest Mall Lookup - Not implemented yet");
        pressEnterToContinue();
    }

    // REMOVED DB NULLPTR CHECK
    void listAllMallsHandler() {
        cls();
        logger->Title("LIST OF ALL MALLS");

        // Removed the !db check as requested
        if (db->getMallTableSize() == 0) {
            logger->Warning("No malls registered yet.");
            pressEnterToContinue();
            return;
        }

        for (int i = 0; i < db->getMallTableSize(); i++) {
            MallNode* current = db->getMallAt(i);
            while (current) {
                logger->Info("Mall ID: " + current->data.mallId +
                    ", Name: " + current->data.name +
                    ", Sector: " + current->data.sector);
                current = current->next;
            }
        }
        pressEnterToContinue();
    }

    void listAllItemsHandler() {
        cls();
        logger->Title("LIST ALL ITEMS IN ALL MALLS");

        // Assuming db check is not needed here based on previous instructions, 
        // or db->getMallTableSize() handles it safely if implemented that way.
        for (int i = 0; i < db->getMallTableSize(); i++) {
            MallNode* mallNode = db->getMallAt(i);
            while (mallNode) {
                logger->Info(">> Mall: " + mallNode->data.name + " (" + mallNode->data.sector + ")");

                if (mallNode->data.productTable.tableSize > 0) {
                    bool hasItems = false;
                    for (int j = 0; j < mallNode->data.productTable.tableSize; j++) {
                        ProductNode* pNode = mallNode->data.productTable.table[j];
                        while (pNode) {
                            logger->Info("   - " + pNode->data.name +
                                " (" + pNode->data.category + ") - PKR " +
                                to_string(pNode->data.price));
                            hasItems = true;
                            pNode = pNode->next;
                        }
                    }
                    if (!hasItems) logger->Info("   (No items registered)");
                }
                else {
                    logger->Info("   (No items registered)");
                }

                cout << endl;
                mallNode = mallNode->next;
            }
        }
        pressEnterToContinue();
    }
};