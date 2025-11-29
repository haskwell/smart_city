#include "SmartCity/SmartCity.h"
#include <ctime>

void seed(SmartCity& city) {
	//insert 1000 people into population with ages 0 to 100
	for (int i = 1; i <= 1000; i++) {
		string name = "Citizen " + to_string(i);
		string cnic = "CIT" + to_string(i);
		int age = rand() % 101; // age between 0 and 100
		Person* person = new Person(name, age, (i % 2 == 0) ? 'M' : 'F', cnic, "Street " + to_string(i), i, "Citizen", "Sector " + to_string(i));
		city.db.people.insert(person);
	}
	//insert 20 pharmacies
	for (int i = 1; i <= 20; i++) {
		string name = "Pharmacy " + to_string(i);
		string id = "PHARM" + to_string(i);
		Pharmacy* pharmacy = new Pharmacy(name, id, "Location " + to_string(i), 10);
		city.db.pharmacies.insert(*pharmacy);
		for (int j = 1; j <= 3; j++) {
			string medName = "Medicine " + to_string(j);
			string formula = "Formula " + to_string(j);
			float price = 10.0f + j;
			Medicine med(medName, formula, price);
			pharmacy->medicineTable.insert(med);
		}
	}
	//insert 20 hospitals
	for (int i = 1; i <= 20; i++) {
		string name = "Hospital " + to_string(i);
		string id = "HOSP" + to_string(i);
		//random beds
		int beds = 20 + (rand() % 30);
		Hospital* hospital = new Hospital(name, id, beds, "Sector " + to_string(i), 5);
		city.db.hospitals.insert(*hospital);
		city.medical.emergencyBedHeap.insert(hospital->id, beds);
	}
	//insert 100 doctors into the population and assign to hospitals
	for (int i = 1; i <= 100; i++) {
		string name = "Doctor " + to_string(i);
		string cnic = "DOC" + to_string(i);
		Doctor* doctor = new Doctor(name, 40 + i, 'M', cnic, "Street " + to_string(i), i, "Doctor", "Sector " + to_string(i), "Specialization " + to_string(i));
		city.db.people.insert(doctor);
		string hospitalId = "HOSP" + to_string((i % 20) + 1);
		Hospital* hospital = city.db.hospitals.search(hospitalId);
		if (hospital) {
			hospital->doctorsTable.insert(doctor);
		}
	}

	//insert ONE doctor into population and assign to hospital
	Person* doctor = new Doctor("Dr. John Doe", 45, 'M', "DOC1001", "123 Main St", 1, "Doctor", "Sector 1", "Cardiology");
	city.db.people.insert(doctor);
	Hospital* hospital = new Hospital("City Hospital", "HOSPP1", 50, "Sector 1", 5);
	city.db.hospitals.insert(*hospital);
	hospital->doctorsTable.insert(dynamic_cast<Doctor*>(doctor));



	//insert ONE pharmacy into database with THREE medicines
	//Pharmacy* pharmacy = new Pharmacy("HealthPlus Pharmacy", "PHARM1", "456 Elm St", 3);
	//city.db.pharmacies.insert(*pharmacy);
	//Medicine med1("Aspirin", "C9H8O4", 5.99f);
	//Medicine med2("Paracetamol", "C8H9NO2", 3.49f);
	//Medicine med3("Ibuprofen", "C13H18O2", 7.89f);
	//pharmacy->medicineTable.insert(med1);
	//pharmacy->medicineTable.insert(med2);
	//pharmacy->medicineTable.insert(med3);
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	SmartCity city;
	seed(city);
    city.run();
    return 0;
}