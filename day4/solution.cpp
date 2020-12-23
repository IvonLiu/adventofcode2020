#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

unordered_map<string, int> key_shift ({
	{"byr", 1<<0},
	{"iyr", 1<<1},
	{"eyr", 1<<2},
	{"hgt", 1<<3},
	{"hcl", 1<<4},
	{"ecl", 1<<5},
	{"pid", 1<<6}
});

bool validatePassport(vector<string> &fields) {
	int sum = 0;
	for (auto it = fields.begin(); it != fields.end(); it++) {
		int idx = it->find(':');
		string key = it->substr(0, idx);
		cout << key << " ";
		if (key_shift.find(key) != key_shift.end()) {
			sum |= key_shift[key];
		}
	}
	bitset<8> b(sum);
	cout << b << endl;
	return sum == (1<<7) - 1;
}

int main() {

	string line;
	ifstream input ("input.txt");
	vector<string> fields;
	int count = 0;

	if (input.is_open()) {
		while (getline(input, line)) {

			if (line.empty()) {
				// End of passport
				if (validatePassport(fields)) {
					count++;
				}
				fields.clear();
				continue;
			}

			stringstream ss(line);
	        while(getline(ss, line, ' ')){
	            fields.push_back(line);
	        }

		}

		if (validatePassport(fields)) {
			count++;
		}

		input.close();
	}

	cout << count << endl;

	return 0;
}