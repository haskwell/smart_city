#include "SmartCity/SmartCity.h"
using namespace std;

int main() {
    SmartCity city;
    //city.seedFromCSV();
    city.seedRandomCity();
    city.run();
    return 0;
}