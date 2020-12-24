#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {

    string line;
    ifstream input ("input.txt");
    unordered_set<char> set;
    unordered_set<char> set2;
    int count = 0;
    bool newGroup = true;

    if (input.is_open()) {
        while (getline(input, line)) {
            if (line.empty()) {
                count += set.size();

                for (auto &c : set) {
                    cout << c;
                }
                cout << endl;
                cout << "---" << endl;

                set.clear();
                newGroup = true;
                continue;
            }

            for (char const &c: line) {
                if (newGroup || set.find(c) != set.end()) {
                    set2.insert(c);
                }
            }
            set = set2;
            set2.clear();
            newGroup = false;
        }
        count += set.size();

        for (auto &c : set) {
            cout << c;
        }
        cout << endl;

        input.close();
    }

    cout << count << endl;

    return 0;
}