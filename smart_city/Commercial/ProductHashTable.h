#pragma once
#include <string>
using namespace std;
class Product {
public:
    string name;
    float price;
    string category;

    Product(string n = "", float p = 0, string c = "")
        : name(n), price(p), category(c)
    {
    }
};

class ProductNode {
public:
    Product data;
    ProductNode* next;

    ProductNode(Product b) : data(b), next(nullptr) {}
};

class ProductHashTable {
public:
    ProductNode** table;
    int tableSize;

    ProductHashTable() : table(nullptr), tableSize(0) {}

    void setUptable(int size) {
        tableSize = size;
        table = new ProductNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    //Add products using hash table
    int hash(string medCategory) {
		int hashValue = 0;
		int primeNumber = 17; // to reduce collisions

        for (int i = 0;  i < medCategory.length(); i++) {
            hashValue = (hashValue * primeNumber + medCategory[i]) % tableSize;
		}

		return hashValue;
    }


    void insert(Product product) {
        int index = hash(product.name);
		ProductNode* newNode = new ProductNode(product);
        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            ProductNode* current = table[index];
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
		}
    }

    //Category-based product search 
    Product* search(const string& product) {
		int index = hash(product);
        ProductNode* current = table[index];
        while (current) {
            if (current->data.name == product) {
                return &current->data;
            }
            current = current->next;
        }
		return nullptr;

    }

    ~ProductHashTable() {
        for (int i = 0; i < tableSize; i++) {
            ProductNode* current = table[i];
            while (current != nullptr) {
                ProductNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] table;
	}
};