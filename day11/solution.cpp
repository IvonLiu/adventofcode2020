#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int countOccupiedNeighbors(vector<vector<char>> &seats, int i, int j) {
	bool hasPrevRow = i > 0;
	bool hasNextRow = i + 1 < seats.size();
	bool hasPrevCol = j > 0;
	bool hasNextCol = j + 1 < seats[i].size();

	int neighbors = 0;
	if (hasPrevRow && hasPrevCol && seats[i-1][j-1] <= '#') neighbors++;
	if (hasPrevRow               && seats[i-1][j  ] <= '#') neighbors++;
	if (hasPrevRow && hasNextCol && seats[i-1][j+1] <= '#') neighbors++;
	if (              hasPrevCol && seats[i  ][j-1] <= '#') neighbors++;
	if (              hasNextCol && seats[i  ][j+1] <= '#') neighbors++;
	if (hasNextRow && hasPrevCol && seats[i+1][j-1] <= '#') neighbors++;
	if (hasNextRow               && seats[i+1][j  ] <= '#') neighbors++;
	if (hasNextRow && hasNextCol && seats[i+1][j+1] <= '#') neighbors++;

	return neighbors;
}

int main() {

	string line;
	ifstream input ("input.txt");
	vector<vector<char>> seats;

	if (input.is_open()) {
		while (getline(input, line)) {
			seats.push_back(vector<char>(line.begin(), line.end()));
		}
		input.close();
	}

	while (true) {
		// cin >> line;
		int newOccupied = 0;
		int newEmpty = 0;
		int count = 0;
		for (int i=0; i<seats.size(); i++) {
			for (int j=0; j<seats[i].size(); j++) {
				// cout << seats[i][j];
				if (seats[i][j] == '.') continue;
				int neighbors = countOccupiedNeighbors(seats, i, j);
				seats[i][j] -= neighbors;
			}
			// cout << endl;
		}
		// cout << "-----" << endl;
		for (int i=0; i<seats.size(); i++) {
			for (int j=0; j<seats[i].size(); j++) {
				if (seats[i][j] == '.') {
					// cout << seats[i][j];
					continue;
				}
				if (seats[i][j] < '.') { // #
					count++;
					if ('#' - seats[i][j] >= 4) {
						newEmpty++;
						seats[i][j] = 'L';
					} else {
						seats[i][j] = '#';
					}
				} else { // 'L'
					if (seats[i][j] == 'L') {
						newOccupied++;
						seats[i][j] = '#';
					} else {
						seats[i][j] = 'L';
					}
				}
				// cout << seats[i][j];
			}
			// cout << endl;
		}

		cout << "Count: " << count << ", ";
		cout << "newOccupied: " << newOccupied << ", ";
		cout << "newEmpty: " << newEmpty << endl;

		if (newOccupied == 0 && newEmpty == 0) {
			cout << count << endl;
			break;
		}
	}

	return 0;
}