#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void rotate(int &dx, int &dy, int val) {
    val = (val + 360) % 360;
    int c = (val % 180 == 0 ? 1 : 0) * (val % 360 == 0 ? 1 : -1);
    int s = (val % 180 == 0 ? 0 : 1) * (val % 270 == 0 ? -1 : 1);
    int new_dx = c * dx - s * dy;
    dy = s * dx + c * dy;
    dx = new_dx;
}

int main() {
    
    string line;
    ifstream input ("input.txt");

    int x = 0;
    int y = 0;
    int dx = 10;
    int dy = 1;

    if (input.is_open()) {
        while (getline(input, line)) {
            char c = line[0];
            int val = stoi(line.substr(1));
            cout << c << val << ": ";
            switch (c) {
                case 'N':
                    dy += val;
                    break;
                case 'S':
                    dy -= val;
                    break;
                case 'E':
                    dx += val;
                    break;
                case 'W':
                    dx -= val;
                    break;
                case 'L':
                    rotate(dx, dy, val);
                    break;
                case 'R':
                    rotate(dx, dy, -val);
                    break;
                case 'F':
                    x += dx * val;
                    y += dy * val;
                    break;
            }
            cout << x << ", " << y << ", " << dx << ", " << dy << endl;
        }
        input.close();
    }

    cout << (abs(x) + abs(y)) << endl;

    return 0;
}