#include "SmartCity/SmartCity.h"

void seed(SmartCity& city) {
    //insert a doctor
	Doctor* doc = new Doctor("Dr. John Doe", 45, 'M', "123", "Maple Street", 101, "doctor", "Downtown", "Cardiology");
	city.db.people.insert(doc);
    //insert a hospital
	Hospital* hosp = new Hospital("City Hospital", "HOSP001", 50, "Downtown", 3);
	city.db.hospitals.insert(*hosp);
	//insert 5 people
	for (int i = 1; i <= 5; i++) {
		string name = "Person " + to_string(i);
		string cnic = "CNIC" + to_string(i);
		Person* person = new Person(name, 30 + i, 'M', cnic, "Street " + to_string(i), i, "Occupation " + to_string(i), "Sector " + to_string(i));
		city.db.people.insert(person);
	}
}

int main() {
    SmartCity city;
	seed(city);
    city.run();
    return 0;
}