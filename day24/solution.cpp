#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

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
			ss << "b1" << b1 << "b2" << b2;
			string key = ss.str();

			if (flipped.erase(key) == 0) {
				flipped.insert(key);
			}
		}
		input.close();
	}

	cout << flipped.size() << endl;

	return 0;
}