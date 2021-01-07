#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    x = 1, y = 0;
    int64_t x1 = 0, y1 = 1;

    while (b != 0) {
        tie(x, x1) = make_tuple(x1, x - (a / b) * x1);
        tie(y, y1) = make_tuple(y1, y - (a / b) * y1);
        tie(a, b) = make_tuple(b, a % b);
    }
    return a;
}

int64_t inverse(int64_t a, int64_t base) {
    a = a % base;
    int64_t x, y;
    int64_t g = gcd(base, a, x, y);
    return ((y % base) + base) % base;
}

int main() {

    string line;
    ifstream input ("input.txt");
    int currTime;
    uint64_t N = 1;
    vector<int> ids;

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
                N *= id;
                ids.push_back(id);
            } else {
                ids.push_back(-1);
            }
        }
        input.close();
    }

    int64_t t = 0;
    for (int i=0; i<ids.size(); i++) {
        int n = ids[i];
        if (n != -1) {
            int64_t a = ((-i % n) + n) % n;
            int64_t c = (int64_t) (N / n);
            int64_t inv = inverse(c, n);
            int64_t b = c * inv;
            t = (t + a * b) % N;
        }
    }

    cout << t << endl;

    return 0;
}