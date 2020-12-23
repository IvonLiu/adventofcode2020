#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {

	string line;
	ifstream input ("input.txt");
	unordered_set<char> set;
	int count = 0;

	if (input.is_open()) {
		while (getline(input, line)) {
			if (line.empty()) {
				count += set.size();
				set.clear();
				continue;
			}

			for (char const &c: line) {
				set.insert(c);
			}
		}
		count += set.size();

		input.close();
	}

	cout << count << endl;

	return 0;
}