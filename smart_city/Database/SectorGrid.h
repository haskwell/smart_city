#pragma once
#include <string>
using namespace std;

class SectorGrid {
	public:
	int rows;
	int cols;
	int count = 0;
	int sectorJump = 25;

	string** grid;

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
		
		for (int i = 0; i < rows; i += sectorJump) {
			for(int j = 0; j < cols; j += sectorJump) {
				if (grid[i][j] == "") {
					grid[i][j] = sectorName;
					count++;
					return Coords(i, j);
				}
			}
		}
	}

	Coords getCoordsBySector(string sectorName) {
		for (int i = 0; i < rows; i += sectorJump) {
			for (int j = 0; j < cols; j += sectorJump) {
				if (grid[i][j] == sectorName) {
					return Coords(i, j);
				}
			}
		}
	}
};