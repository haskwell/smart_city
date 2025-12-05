#pragma once
#include <string>
using namespace std;

class SectorGrid {
	public:
	int rows;
	int cols;
	int count = 0;
	int sectorJump = 1;

	string** grid;

	unsigned int seed = 123456;
	unsigned int randomNumber() {
		//Linear Congruential Generator
		seed = (21433103u * seed + 32183u) % 2143245289u;
		return seed;
	}

	void setUpGrid(int r, int c)
	{
		rows = r;
		cols = c;
		grid = new string * [rows];
		for (int i = 0; i < rows; i++) {
			grid[i] = new string[cols];
			for (int j = 0; j < cols; j++) {
				grid[i][j] = "";
			}
		}
	}

	Coords addSectorIntoGrid(const string& sectorName) {

		if (count >= rows * cols) {
			return Coords(-1, -1);
		}

		int total = rows * cols;
		for (int k = 0; k < total; k++) {
			int i = randomNumber() % rows;
			int j = randomNumber() % cols;
			if (grid[i][j] == "") {
				grid[i][j] = sectorName;
				count++;
				cout << "\nAdded sector: " << sectorName << " and count is: " << count << endl;
				return Coords(i, j);
			}
		}
		return Coords(-1, -1);
		//for (int i = 0; i < rows; i++) {
		//	for(int j = 0; j < cols; j++) {
		//		if (grid[i][j] == "") {
		//			grid[i][j] = sectorName;
		//			count++;
		//			return Coords(i, j);
		//		}
		//	}
		//}
	}

	Coords getCoordsBySector(string sectorName) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == sectorName) {
					return Coords(i, j);
				}
			}
		}
	}
};