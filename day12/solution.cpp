#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	
	string line;
	ifstream input ("input.txt");

	pair<int, int> DIRS [] {
		{ 1,  0},
		{ 0, -1},
		{-1,  0},
		{ 0,  1}
	};

	int x = 0;
	int y = 0;
	int dir = 0;

	if (input.is_open()) {
		while (getline(input, line)) {
			char c = line[0];
			int val = stoi(line.substr(1));
			cout << c << val << ": ";
			switch (c) {
				case 'N':
					y += val;
					break;
				case 'S':
					y -= val;
					break;
				case 'E':
					x += val;
					break;
				case 'W':
					x -= val;
					break;
				case 'L':
					val /= 90;
					dir = (((dir - val) % 4) + 4) % 4;
					break;
				case 'R':
					val /= 90;
					dir = (dir + val) % 4;
					break;
				case 'F':
					x += DIRS[dir].first * val;
					y += DIRS[dir].second * val;
					break;
			}
			cout << x << ", " << y << ", " << dir << endl;
		}
		input.close();
	}

	cout << (abs(x) + abs(y)) << endl;

	return 0;
}