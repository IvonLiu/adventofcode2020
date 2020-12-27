#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {

	string line;
	ifstream input ("input.txt");
	unordered_set<int> jolts;
	int maxJolt = 0;

	if (input.is_open()) {
		while (getline(input, line)) {
			int val = stoi(line);
			if (val > maxJolt) {
				maxJolt = val;
			}
			jolts.insert(val);
		}
		input.close();
	}

	int jolt = 0;
	int count1 = 0;
	int count3 = 1;

	while (jolt < maxJolt) {
		bool found = false;
		for (int i=1; i<=3; i++) {
			if (jolts.find(jolt + i) != jolts.end()) {
				found = true;
				jolt = jolt + i;
				if (i == 1) count1++;
				if (i == 3) count3++;
				break;
			}
		}
		if (!found) {
			break;
		}
	}

	cout << count1 << " * " << count3 << " = " << (count1 * count3) << endl;

	return 0;
}