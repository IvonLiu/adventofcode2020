#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {

	string line;
	ifstream input ("input.txt");
	int currTime;
	int minID;
	int minWait;

	if (input.is_open()) {
		// Get current minute
		getline(input, line);
		currTime = stoi(line);

		// Get bus IDs
		getline(input, line);
		stringstream ss (line);

		while (getline(ss, line, ',')) {
			if (line[0] != 'x') {
				int id = stoi(line);
				int wait = id - (currTime % id);
				if (wait < minWait) {
					minID = id;
					minWait = wait;
				}
			}
		}
		input.close();
	}

	cout << minID << " * " << minWait << " = " << (minID * minWait) << endl;

	return 0;
}