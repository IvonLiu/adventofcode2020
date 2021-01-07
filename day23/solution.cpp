#include <iostream>
#include <string>
using namespace std;

const int NUM_CUPS = 1000000;
const int NUM_MOVES = 10000000;

// const int NUM_CUPS = 9;
// const int NUM_MOVES = 100;

void move(int (&ring)[NUM_CUPS], int &current) {
    int a = ring[current];
    int b = ring[a];
    int c = ring[b];

    int dest = ((current - 1) + NUM_CUPS) % NUM_CUPS;
    while (dest == a || dest == b || dest == c) {
        dest = ((dest - 1) + NUM_CUPS) % NUM_CUPS;
    }

    ring[current] = ring[c];
    ring[c] = ring[dest];
    ring[dest] = a;

    current = ring[current];
}

int main() {
    string input = "476138259";
    int ring[NUM_CUPS];

    int current;
    int a = -1;
    for (char &c : input) {
        int b = c - '1';
        if (a >= 0) {
            ring[a] = b;
        } else {
            current = b;
        }
        a = b;
    }
    for (int i=a+1; i<NUM_CUPS; i++) {
        ring[a] = i;
        a = i;
    }
    ring[a] = current;

    for (int i=0; i<NUM_MOVES; i++) {
        move(ring, current);
    }

    uint64_t x = ring[1-1] + 1;
    uint64_t y = ring[x-1] + 1;
    uint64_t z = x * y;

    cout << x << " * " << y << " = " << z << endl;
}