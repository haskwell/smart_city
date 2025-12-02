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
        cin.ignore();
    }

    void cls() {
        cout << "\033[2J\033[H";
    }

public:
	MallSystem(Database* database = nullptr, CityLogger* log = nullptr) : db(database), logger(log) {}


    bool addMall(Mall* mall)
    {
        if (!db)
        {
            return false;
        }

        if (db->searchMall(mall->mallId))
        {
			logger->Warning("Mall with ID '" + mall->mallId + "' already exists!");
            delete mall;
			return false;
        }

        db->insertMall(*mall);
        
		return true;
    }

  

    void registerMallsHandler() {
        cls();
        //cout << ">>> Register Malls - Not implemented yet\n\n";

		logger->Title("REGISTER NEW MALL");

		string mallID, name, sector;
		logger->Prompt("Enter Mall ID: ");

        cin >> mallID;
		cin.ignore();

		logger->Prompt("Enter Mall Name: ");
		getline(cin, name);

		logger->Prompt("Enter Mall Sector: ");
		getline(cin, sector);

		Mall* newMall = new Mall(mallID, name, sector);

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


    bool addProduct(Product product, Mall* mall) {
        if (db == nullptr || mall == nullptr) {
            return false;
		}

        if (mall->productTable.search(product.name)) {
            logger->Warning("Product with name '" + product.name + "' already exists in mall '" + mall->name + "'!");
            return false;
        }

		mall->productTable.insert(product);
		logger->Ok("Product " + product.name + " added to Mall " + mall->name + ".");
        
        return true;
    }

    void addItemsHandler() {
        cls();
        //cout << ">>> Add Items to Shops - Not implemented yet\n\n";
		logger->Title("ADD ITEM TO MALL");
		string mallID;
		logger->Prompt("Enter Mall ID: ");

		cin >> mallID;
		cin.ignore();

		Mall* mall = db->searchMall(mallID);

        if (mall == nullptr)
        {
			logger->Error("Mall with ID '" + mallID + "' not found!");  
            pressEnterToContinue();
			return;
        }
        
        int count;
		logger->Prompt("Enter number of items to add: ");
		cin >> count;
        cin.ignore();

        for (int i = 0; i < count; i++)
        {
            string name, category;
            float price;


            logger->Info("------Product" + to_string(i + 1) + " Details------");
            logger->Prompt("Enter Product Name: ");
            getline(cin, name);

			logger->Prompt("Enter Product Category: ");
			getline(cin, category);

			logger->Prompt("Enter Product Price: ");
			cin >> price;
			cin.ignore();

            Product p(name, price, category);
			addProduct(p, mall);

        }

        pressEnterToContinue();
    }

    void itemSearchHandler() {
        cls();
        //cout << ">>> Item Search (Category Based) - Not implemented yet\n\n";
		
        logger->Title("SEARCH ITEM (CATEGORY BASED)");

        string mallID, category;

        logger->Prompt("Enter Mall ID to seach in: ");

        cin >> mallID;
        cin.ignore();

        Mall* mall = db->malls.search(mallID);

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
        //cout << ">>> Find Nearest Mall - Not implemented yet\n\n";
        
        logger->Title("NEAREST MALL LOOKUP");
        logger->Info(">>> Nearest Mall Lookup - Not implemented yet");
        
        
        pressEnterToContinue();
    }

    //print all malls

    //print all items

    void listAllMallsHandler() {
        cls();
        logger->Title("LIST OF ALL MALLS");

        if (!db || db->malls.tableSize == 0) {
            logger->Warning("No malls registered yet.");
            pressEnterToContinue();
            return;
        }

        for (int i = 0; i < db->malls.tableSize; i++) {
            MallNode* current = db->malls.table[i];
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

        if (!db) return;

        for (int i = 0; i < db->malls.tableSize; i++) {
            MallNode* mallNode = db->malls.table[i];
            while (mallNode) {
                logger->Info(">> Mall: " + mallNode->data.name + " (" + mallNode->data.sector + ")");

                // Check if this mall has an initialized product table
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