#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <cmath>

using namespace std;
typedef vector<vector <int> > matrix;

int NumLength(int x){
	for (int i = 1; i < 6; i++) {
		if (x < pow(10, i)) {
			return i;
		}
	}
}

void spacer(int spaces) {
	for (int i = 0; i < spaces; i++) {
		cout << " ";
	}
}

void display_grid(matrix grid) {
	cout << endl;
	int spaces;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << grid[i][j];
			spaces = 8 - NumLength(grid[i][j]);
			spacer(spaces);
		}
		cout << endl;
	}
	cout << endl;
}

void def(matrix& grid) {
	for (int i = 0; i < 4; i++) {
		vector<int> row;
		for (int j = 0; j < 4; j++) {
			row.push_back(0);
		}
		grid.push_back(row);
	}
	grid[3][3] = 2;
}

void rightshift(matrix& grid) {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j >= 0; j--) {
			if (grid[i][j] == 0) {
				for (int q = j - 1; q >= 0; q--) {
					if (grid[i][j] == 0) {
						if (grid[i][q] != 0) {
							grid[i][j] = grid[i][q];
							grid[i][q] = 0;
						}
					}
				}
			}
		}
	}
}

void downshift(matrix& grid) {
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i >= 0; i--) {
			if (grid[i][j] == 0) {
				for (int q = i - 1; q >= 0; q--) {
					if (grid[i][j] == 0) {
						if (grid[q][j] != 0) {
							grid[i][j] = grid[q][j];
							grid[q][j] = 0;
						}
					}
				}
			}
		}
	}
}

void leftshift(matrix& grid) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (grid[i][j] == 0) {
				for (int q = j + 1; q  < 4; q++) {
					if (grid[i][j] == 0) {
						if (grid[i][q] != 0) {
							grid[i][j] = grid[i][q];
							grid[i][q] = 0;
						}
					}
				}
			}
		}
	}
}

void upshift(matrix& grid) {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (grid[i][j] == 0) {
				for (int q = i + 1; q < 4; q++) {
					if (grid[i][j] == 0) {
						if (grid[q][j] != 0) {
							grid[i][j] = grid[q][j];
							grid[q][j] = 0;
						}
					}
				}
			}
		}
	}
}

void rightadd(matrix& grid) {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			if (grid[i][j] == grid[i][j-1]) {
				grid[i][j] = 2 * grid[i][j];
				grid[i][j-1] = 0;
			}
		}
	}
}

void downadd(matrix& grid) {
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i > 0; i--) {
				if (grid[i][j] == grid[i-1][j]) {
					grid[i][j] = 2 * grid[i][j];
					grid[i-1][j] = 0;
			}
		}
	}
}

void upadd(matrix& grid) {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
				if (grid[i][j] == grid[i+1][j]) {
					grid[i][j] = 2 * grid[i][j];
					grid[i+1][j] = 0;
			}
		}
	}
}

void leftadd(matrix& grid) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
				if (grid[i][j] == grid[i][j+1]) {
					grid[i][j] = 2 * grid[i][j];
					grid[i][j+1] = 0;
			}
		}
	}
}

void shift(matrix& grid, char dir) {
	if (dir == 'd') {
		rightshift(grid);
		rightadd(grid);
		rightshift(grid);
	}
	if (dir == 's') {
		downshift(grid);
		downadd(grid);
		downshift(grid);
	}
	if (dir == 'a') {
		leftshift(grid);
		leftadd(grid);
		leftshift(grid);
	}
	if (dir == 'w') {
		upshift(grid);
		upadd(grid);
		upshift(grid);
	}
}

void addtwo(matrix& grid) {
	int n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (grid[i][j] == 0) {
				n++;
			}
		}
	}
	n = rand() % n + 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (grid[i][j] == 0) {
				n--;
				if (n == 0) {
					grid[i][j] = 2;
				}
			}
		}
	}
}

bool moremoves(matrix grid) {
	matrix grid2 = grid;
	shift(grid, 'd');
	shift(grid, 's');
	shift(grid, 'a');
	shift(grid, 'w');
	if (grid2 == grid) {
		return false;
	}
}

int main() {
	bool moves;
	matrix grid;
	ifstream infile;
	string filename;
	char dir;
	cout << "enter initial configuration file name:" << endl;
	cin >> filename;
	infile.open(filename.c_str());
	if (!infile.is_open()) {
		cout << "file not found, default start configuration:" << endl;
		def(grid);
	}
	else {
		int num;
		for (int i = 0; i < 4; i++) {
			vector<int> row;
			for (int j = 0; j < 4; j++) {
				infile >> num;
				row.push_back(num);
			}
			grid.push_back(row);
		}
	}
	display_grid(grid);
	srand(time(NULL));
	matrix grid2;
	moves = moremoves(grid);
	while (moves) {
		cin >> dir;
		grid2 = grid;
		shift(grid, dir);
		if (grid2 != grid) {
			addtwo(grid);
			display_grid(grid);
		}
		moves = moremoves(grid);
	}
	cout << endl << endl << "game over" << endl;
	return 0;
}


