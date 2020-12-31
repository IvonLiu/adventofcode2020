#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    uint64_t ts = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();

    const int NUM_TURNS = 30000001;
    int input[] {0,1,4,13,15,12,16};

    int* turns = new int[NUM_TURNS];
    fill_n(turns, NUM_TURNS, -1);

    int num = input[0];
    int prevNum = 0;

    for (int i=0; i<NUM_TURNS; i++) {
        prevNum = num;
        if (i-1 < size(input)) {
            num = input[i-1];
        } else {
            if (turns[num] != -1) {
                num = i - 1 - turns[num];
            } else {
                num = 0;
            }
        }
        turns[prevNum] = i - 1;
    }

    uint64_t te = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();

    cout << num << endl;
    cout << "Took " << (te - ts) << "ms" << endl;

    delete[] turns;

    return 0;
}