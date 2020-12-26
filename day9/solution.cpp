#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

class Node {
    public:
        long val;
        Node* next;
        Node (long val) : val(val) {}
};

unordered_map<long, int> map;
Node* start;
Node* last;


bool valid(long &val, long &a, long &b) {
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

int main() {
    string line;
    ifstream input ("input.txt");

    int count = 0;
    int preamble = 25;

    if (input.is_open()) {
        while (getline(input, line)) {
            long val = stol(line);
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
                long a, b;
                if (!valid(val, a, b)) {
                    cout << val << endl;
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

    while (start) {
        Node* next = start->next;
        delete start;
        start = next;
    }

    return 0;
}