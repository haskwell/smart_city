#pragma once
#include <string>
using namespace std;
struct Medicine {
    string name;
    string formula;
    float price;

    Medicine(string n = "", string f = "", float p = 0.0f)
        : name(n), formula(f), price(p) {
    }
};