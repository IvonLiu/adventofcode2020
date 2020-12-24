#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

unordered_map<string, int> key_shift ({
    {"byr", 1<<0},
    {"iyr", 1<<1},
    {"eyr", 1<<2},
    {"hgt", 1<<3},
    {"hcl", 1<<4},
    {"ecl", 1<<5},
    {"pid", 1<<6}
});

bool fieldExists(string &field, string &key, string &val) {
    int idx = field.find(':');
    key = field.substr(0, idx);
    val = field.substr(idx + 1);
    return key_shift.find(key) != key_shift.end();
}

bool validateField(string &field, string &key, string &val) {
    if (fieldExists(field, key, val)) {
        try {
            if (key == "byr") {
                int num = stoi(val);
                return 1920 <= num && num <= 2002;
            } else if (key == "iyr") {
                int num = stoi(val);
                return 2010 <= num && num <= 2020;
            } else if (key == "eyr") {
                int num = stoi(val);
                return 2020 <= num && num <= 2030;
            } else if (key == "hgt") {
                int num = stoi(val.substr(0, val.length() - 2));
                string unit = val.substr(val.length() - 2);
                if (unit == "cm") {
                    return 150 <= num && num <= 193;
                } else if (unit == "in") {
                    return 59 <= num && num <= 76;
                } else {
                    return false;
                }
            } else if (key == "hcl") {
                int num = stoi(val.substr(1), nullptr, 16);
                return val[0] == '#' && val.length() == 7;
            } else if (key == "ecl") {
                return val == "amb"
                    || val == "blu"
                    || val == "brn"
                    || val == "gry"
                    || val == "grn"
                    || val == "hzl"
                    || val == "oth";
            } else if (key == "pid") {
                int num = stoi(val);
                return 0 <= num && num <= 999999999 && val.length() == 9;
            }
        } catch (invalid_argument &ia) {
            return false;
        } catch (out_of_range &oor) {
            return false;
        }
    }
    return false;
}

bool validatePassport(vector<string> &fields) {
    int sum = 0;
    for (auto it = fields.begin(); it != fields.end(); it++) {
        string key, val;
        if (validateField(*it, key, val)) {
            sum |= key_shift[key];
        }
        cout << key << " ";
    }
    bitset<8> b(sum);
    cout << b << endl;
    return sum == (1<<7) - 1;
}

int main() {

    string line;
    ifstream input ("input.txt");
    vector<string> fields;
    int count = 0;

    if (input.is_open()) {
        while (getline(input, line)) {

            if (line.empty()) {
                // End of passport
                if (validatePassport(fields)) {
                    count++;
                }
                fields.clear();
                continue;
            }

            stringstream ss(line);
            while(getline(ss, line, ' ')){
                fields.push_back(line);
            }

        }

        if (validatePassport(fields)) {
            count++;
        }

        input.close();
    }

    cout << count << endl;

    return 0;
}