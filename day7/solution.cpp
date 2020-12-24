#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>
using namespace std;

class Bag {
	public:
		Bag (string name) : name(name) { }
		string name;
		vector<Bag*> parents;
		vector<pair<Bag*, int>> children;
};

Bag* getBag(unordered_map<string, Bag*> &map, string &name) {
	if (map.find(name) == map.end()) {
		map[name] = new Bag(name);
	}
	return map[name];
}

int getNumParents(Bag* start, bool verbose = false) {
	unordered_set<Bag*> visited;
	queue<Bag*> q;
	q.push(start);

	while (!q.empty()) {
		Bag* curr = q.front();
		q.pop();
		visited.insert(curr);

		for (auto &p : curr->parents) {
			if (visited.find(p) == visited.end()) {
				p->children.clear();
				p->children.push_back(pair<Bag*, int>(curr, 0));
				q.push(p);
			}
		}
	}

	if (verbose) {
		for (auto &bag : visited) {
			Bag* curr = bag;
			if (curr == start) continue;
			while (!curr->children.empty() && curr != start) {
				cout << curr->name << " -> ";
				curr = curr->children[0].first;
			}
			cout << curr->name << endl;
		}
	}

	return visited.size() - 1; // -1 because starting bag by itself doesn't count
}

int getNumBags(Bag* bag) {
	if (!bag) {
		return 0;
	}

	int totalBags = 1;
	for (auto &p : bag->children) {
		Bag* b = p.first;
		int count = p.second;
		totalBags += getNumBags(b) * count;
	}
	return totalBags;
}

int main() {

	string line;
	ifstream input ("input.txt");
	unordered_map<string, Bag*> map;

	if (input.is_open()) {
		while (getline(input, line)) {
			string sep = " bags contain ";
			int idx = line.find(sep);
			string name = line.substr(0, idx);
			// cout << name << " -> ";
			Bag* bag = getBag(map, name);

			if (line.find("no other bags") == string::npos) {
				string childStr = line.substr(idx + sep.length());
				stringstream ss(childStr);
				string token;
				while (getline(ss, token, ',')) {
					int start = token.find(" ", 1) + 1;
					int end = token.find(" bag");
					int len = end - start;
					string childName = token.substr(start, len);

					string countStr = "";
					int countStart = token.find(" ") + 1;
					if (countStart == start) {
						countStr = token.substr(0, countStart - 1);
					} else {
						int countLen = start - countStart - 1;
						countStr = token.substr(countStart, countLen);
					}
					int childCount = 0;
					try {
						childCount = stoi(countStr);
					} catch (invalid_argument &ia) {}

					Bag* childBag = getBag(map, childName);
					bag->children.push_back(pair<Bag*, int>(childBag, childCount));
					childBag->parents.push_back(bag);

					// cout << childCount << " " << childName << ", ";
				}
			}
			// cout << endl;
		}
		input.close();
	}

	Bag* start = map["shiny gold"];
	// int numParents = getNumParents(start);
	int numBags = getNumBags(start) - 1; // -1 because starting bag doesn't count

	cout << numBags << endl;

	// memory cleanup
	for (auto &pair : map) {
		delete pair.second;
	}

	return 0;
}
