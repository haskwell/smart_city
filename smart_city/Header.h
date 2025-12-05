#pragma once
#include <string>
using namespace std;

class SectorGrid {
	public:
	int rows;
	int cols;
	float cellWidth;
	float cellHeight;
	int currentX = 0;
	int currentY = 0;
	int count = 0;

	string** grid;

	SectorGrid(int r, int c, float w, float h)
		: rows(r), cols(c), cellWidth(w), cellHeight(h) {
		grid = new string * [rows];
		for (int i = 0; i < rows; i++) {
			grid[i] = new string[cols];
			for (int j = 0; j < cols; j++) {
				grid[i][j] = "";
			}
		}
	}

	bool getNextSlot() {

	}

	bool addSectorIntoGrid(const string& sectorName) {
		// how its gonna work is each sector is inserted in manhattan distance layers

		if (count >= rows * cols) {
			return false;
		}
		
		while (true) {

		}


	}
};