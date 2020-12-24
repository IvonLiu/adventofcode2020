#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

int main() {
	vector<tuple<string, int, bool>> instructions;

	string line;
	ifstream input ("input.txt");

	if (input.is_open()) {
		while (getline(input, line)) {
			int idx = line.find(" ");
			string cmd = line.substr(0, idx);
			int val = stoi(line.substr(idx+1));
			instructions.push_back(make_tuple(cmd, val, false));
		}
		input.close();
	}

	int accumulator = 0;
	auto inst = instructions.begin();

	while (!get<2>(*inst)) {
		string cmd = get<0>(*inst);
		int val = get<1>(*inst);
		get<2>(*inst) = true;

		cout << cmd << " " << val << " | " << accumulator << endl;

		if (cmd == "acc") {
			accumulator += val;
			inst++;
		} else if (cmd == "jmp") {
			inst += val;
		} else {
			inst++;
		}
	}

	cout << accumulator << endl;
}