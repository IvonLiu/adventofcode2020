#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
	vector<string> trees;
	string line;
	ifstream input ("input.txt");
	if (input.is_open()) {
		while (getline(input, line)) {
			trees.push_back(line);
		}
		input.close();
	}

	int x = 0;
	int n = trees[0].length();
	int count = 0;

	for (auto it = trees.begin(); it != trees.end(); it++) {
		char c = (*it)[x];
		if (c == '#') {
			count++;
		}
		x = (x + 3) % n;
	}

	cout << count << endl;
	return 0;
}