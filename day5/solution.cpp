#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    string line;
    ifstream input ("input.txt");
    int maxId = 0;
    int minId = INT_MAX;
    int x = 0;

    if (input.is_open()) {
        while (getline(input, line)) {
            int row = 0;
            int seat = 0;
            for (int i=0; i<7; i++) {
                if (line[i] == 'B') {
                    row |= 1 << (6 - i);
                }
            }
            for (int i=7; i<10; i++) {
                if (line[i] == 'R') {
                    seat |= 1 << (9 - i);
                }
            }
            int id = row * 8 + seat;
            if (id > maxId) {
                maxId = id;
            }
            if (id < minId) {
                minId = id;
            }
            x = x ^ id;
        }
        input.close();
    }

    for (int i=minId; i<=maxId; i++) {
        x = x ^ i;
    }

    cout << maxId << endl;
    cout << x << endl;
}