#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {

    string line;
    ifstream input ("input.txt");
    unordered_set<int> jolts;
    int maxJolt = 0;

    if (input.is_open()) {
        while (getline(input, line)) {
            int val = stoi(line);
            if (val > maxJolt) {
                maxJolt = val;
            }
            jolts.insert(val);
        }
        input.close();
    }

    int jolt = 0;
    int count1 = 0;
    int count3 = 1;

    while (jolt < maxJolt) {
        bool found = false;
        for (int i=1; i<=3; i++) {
            if (jolts.find(jolt + i) != jolts.end()) {
                found = true;
                jolt = jolt + i;
                if (i == 1) count1++;
                if (i == 3) count3++;
                break;
            }
        }
        if (!found) {
            break;
        }
    }

    cout << count1 << " * " << count3 << " = " << (count1 * count3) << endl;

    vector<long long> combinations (maxJolt+1, 0);
    combinations[0] = 1;

    for (int i = 0; i <= maxJolt; i++) {
        if (jolts.find(i) != jolts.end()) {
            combinations[i] += i - 3 >= 0 ? combinations[i-3] : 0;
            combinations[i] += i - 2 >= 0 ? combinations[i-2] : 0;
            combinations[i] += i - 1 >= 0 ? combinations[i-1] : 0;
            cout << i << ": " << combinations[i] << endl;
        }
    }

    return 0;
}