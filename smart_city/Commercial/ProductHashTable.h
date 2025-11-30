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

    int hash(string busNo) { return 0; }

    void insert(Product b) {}

    Product* search(string busNo) { return 0; }

    ~ProductHashTable() {
        for (int i = 0; i < tableSize; i++) {
            delete[]table[i];
        }
        delete[]table;
    }
};