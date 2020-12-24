#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int checkTree(int dx, int dy) {
    int x = 0;
    int y = 0;
    int count = 0;

    string line;
    ifstream input ("input.txt");
    if (input.is_open()) {
        while (getline(input, line)) {
            if (y % dy == 0) {
                char c = line[x];
                if (c == '#') {
                    count++;
                }
                x = (x + dx) % line.length();
            }
            y++;
        }
        input.close();
    }

    return count;
}

int main() {

    int slopes[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    long product = 1;

    for (auto &slope : slopes) {
        int count = checkTree(slope[0], slope[1]);
        cout << slope[0] << ", " << slope[1] << " => " << count << endl;
        product *= count;
    }

    cout << product << endl;

    return 0;
}