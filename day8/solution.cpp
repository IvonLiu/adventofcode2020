#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_set>
using namespace std;

bool testLoop(vector<tuple<string, int>> &instructions, int &accumulator) {
    accumulator = 0;
    auto inst = instructions.begin();
    unordered_set<int> visited;

    cout << "Testing loop " << inst - instructions.begin() << endl;

    while (visited.find(inst - instructions.begin()) == visited.end() && inst < instructions.end()) {
        string cmd = get<0>(*inst);
        int val = get<1>(*inst);
        visited.insert(inst - instructions.begin());

        if (cmd == "acc") {
            accumulator += val;
            inst++;
        } else if (cmd == "jmp") {
            inst += val;
        } else {
            inst++;
        }

        cout << cmd << " " << val << " | " << accumulator << " | " << inst - instructions.begin() << endl;
    }

    return inst >= instructions.end();
}

int fixLoop(vector<tuple<string, int>> &instructions) {
    int accumulator;
    for (auto &inst : instructions) {
        if (get<0>(inst) == "jmp") {
            get<0>(inst) = "nop";
            if (testLoop(instructions, accumulator)) {
                return accumulator;
            }
            get<0>(inst) = "jmp";
        } else if (get<0>(inst) == "nop") {
            get<0>(inst) = "jmp";
            if (testLoop(instructions, accumulator)) {
                return accumulator;
            }
            get<0>(inst) = "nop";
        }
    }
    return -1;
}

int main() {
    vector<tuple<string, int>> instructions;

    string line;
    ifstream input ("input.txt");

    if (input.is_open()) {
        while (getline(input, line)) {
            int idx = line.find(" ");
            string cmd = line.substr(0, idx);
            int val = stoi(line.substr(idx+1));
            instructions.push_back(make_tuple(cmd, val));
        }
        input.close();
    }

    //int accumulator;
    //bool noLoop = testLoop(instructions, accumulator);

    int accumulator = fixLoop(instructions);

    cout << accumulator << endl;
}