#pragma once
#include <iostream>
#include <string>
using namespace std;

class CityLogger {
private:
	//colors
	string red = "\033[31m";
	string green = "\033[32m";
	string yellow = "\033[33m";
	string blue = "\033[34m";
	string magenta = "\033[35m";
	string cyan = "\033[36m";
	string clear = "\033[0m";

public:

	void Ok(const string& message) {
		cout << green << "[OK] " << clear << message << endl;
	}

	void Error(const string& message) {
		cout << red << "[ERROR] " << clear << message << endl;
	}

	void Warning(const string& message) {
		cout << yellow << "[WARNING] " << clear << message << endl;
	}

	void Info(const string& message) {
		cout << cyan << "[INFO] " << clear << message << endl;
	}

	void Prompt(const string& message) {
		cout << magenta << message << clear;
	}

	void Title(const string& message) {
		cout << clear <<"--------------------------------\n";
		cout << blue << "=== " << message << " ===" << clear << endl;
		cout << "--------------------------------\n";
	}

};