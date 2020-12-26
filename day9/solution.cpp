#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Node {
    public:
        long long val;
        Node* next;
        Node (long long val) : val(val) {}
};

unordered_map<long long, int> map;
Node* start;
Node* last;
vector<long long> values;


bool valid(long long &val, long long &a, long long &b) {
    Node* node = start;
    while (node) {
        if (map.find(val - node->val) != map.end()) {
            if (val - node->val != node->val || map[node->val] > 1) {
                a = node->val;
                b = val - node->val;
                return true;
            }
        }
        node = node->next;
    }
    return false;
}

long long findContinuous(long long &invalid) {
    auto a = values.begin();
    auto b = values.begin();
    long long sum = 0;

    while (a != values.end() && b != values.end()) {
        sum += *b;
        while (sum > invalid && a != values.end()) {
            sum -= *a;
            a++;
        }
        if (sum == invalid) {
            cout << "found" << endl;
            break;
        }
        b++;
    }
    cout << endl;

    int min = INT_MAX;
    int max = INT_MIN;
    for (auto it = a; it <= b; it++) {
        cout << *it << " + ";
        if (*it < min) {
            min = *it;
        }
        if (*it > max) {
            max = *it;
        }
    }
    cout << endl;

    return min + max;
}

int main() {
    string line;
    ifstream input ("input.txt");

    int count = 0;
    int preamble = 25;
    long long invalid;

    if (input.is_open()) {
        while (getline(input, line)) {
            long long val = stoll(line);
            values.push_back(val);

            if (count < preamble) {
                Node* node = new Node(val);
                if (!start) {
                    start = node;
                    last = node;
                } else {
                    last->next = node;
                    last = last->next;
                }

                count++;
            } else {
                long long a, b;
                if (!valid(val, a, b)) {
                    cout << val << endl;
                    invalid = val;
                    break;
                } else {
                    cout << val << " = " << a << " + " << b << endl;
                }

                // update the map
                if (map[start->val] == 1) {
                    map.erase(start->val);
                } else {
                    map[start->val]--;
                }

                // update the linkedlist
                Node* node = start;
                start = start->next;
                node->val = val;
                node->next = nullptr;
                last->next = node;
                last = node;
            }

            if (map.find(val) != map.end()) {
                map[val]++;
            } else {
                map[val] = 1;
            }
        }
        input.close();
    }

    long long continuous = findContinuous(invalid);
    cout << continuous << endl;

    while (start) {
        Node* next = start->next;
        delete start;
        start = next;
    }

    return 0;
}