#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

void parse(const string &key, int &b1, int &b2) {
	int pos = key.find("n");
	b1 = stoi(key.substr(1, pos-1));
	b2 = stoi(key.substr(pos+1));
}

vector<string>* neighbors(const string &key) {
	vector<string>* ns = new vector<string>();
	int b1, b2;
	parse(key, b1, b2);
	int directions[6][2] = {
		{2, 0},
		{1, -1},
		{-1, -1},
		{-2, 0},
		{-1, 1},
		{1, 1}
	};
	for (auto &dir : directions) {
		int n1 = b1 + dir[0];
		int n2 = b2 + dir[1];
		ostringstream ss;
		ss << "e" << n1 << "n" << n2;
		ns->push_back(ss.str());
	}

	return ns;
}

void step(unordered_set<string> &flipped) {
	unordered_map<string, int> neighborCounts;
	for (const string &key : flipped) {
		vector<string>* ns = neighbors(key);
		for (string &n : *ns) {
			if (neighborCounts.find(n) == neighborCounts.end()) {
				neighborCounts[n] = 1;
			} else {
				neighborCounts[n]++;
			}
		}
		delete ns;
	}

	unordered_set<string> newFlipped;
	for (const auto &pair : neighborCounts) {
		if (pair.second == 2 ||
			(pair.second == 1 && flipped.find(pair.first) != flipped.end())) {
			newFlipped.insert(pair.first);
		}
	}
	flipped = newFlipped;
}

int main() {

	string line;
	ifstream input ("input.txt");
	unordered_set<string> flipped;

	if (input.is_open()) {
		while (getline(input, line)) {

			int b1 = 0;
			int b2 = 0;

			char prev = 0;
			for (char &c : line) {
				if (c == 's' || c == 'n') {
					prev = c;
				} else {
					if (prev == 0) {
						b1 += c == 'e' ? 2 : -2;
					} else if (prev == 'n') {
						b2++;
						b1 += c == 'e' ? 1 : -1;
					} else if (prev == 's') {
						b2--;
						b1 += c == 'e' ? 1 : -1;
					}
					prev = 0;
				}
			}

			ostringstream ss;
			ss << "e" << b1 << "n" << b2;
			string key = ss.str();

			if (flipped.erase(key) == 0) {
				flipped.insert(key);
			}
		}
		input.close();
	}

	cout << flipped.size() << endl;

	for (int i=1; i<=100; i++) {
		step(flipped);
		cout << "Day " << i << ": " << flipped.size() << endl;
	}

	return 0;
}