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
		vector<Bag*> children;
};

Bag* getBag(unordered_map<string, Bag*> &map, string &name) {
	if (map.find(name) == map.end()) {
		map[name] = new Bag(name);
	}
	return map[name];
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
			//cout << name << " -> ";
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
					//cout << childName << ", ";

					Bag* childBag = getBag(map, childName);
					bag->children.push_back(childBag);
					childBag->parents.push_back(bag);
				}
			}
			//cout << endl;
		}
		input.close();
	}

	unordered_set<Bag*> visited;
	queue<Bag*> q;
	Bag* start = map["shiny gold"];
	q.push(start);

	while (!q.empty()) {
		Bag* curr = q.front();
		q.pop();
		visited.insert(curr);

		for (auto &p : curr->parents) {
			if (visited.find(p) == visited.end()) {
				p->children.clear();
				p->children.push_back(curr);
				q.push(p);
			}
		}
	}

	// for (auto &bag : visited) {
	// 	cout << bag->name << ": ";
	// 	for (auto &child : bag->children) {
	// 		cout << child->name << ", ";
	// 	}
	// 	cout << endl;
	// }

	for (auto &start : visited) {
		Bag* bag = start;
		if (bag->name == "shiny gold") continue;
		while (!bag->children.empty() && bag->name != "shiny gold") {
			cout << bag->name << " -> ";
			bag = bag->children[0];
		}
		cout << bag->name << endl;
	}

	cout << visited.size() - 1 << endl; // -1 because shiny gold by itself doesn't count

	// memory cleanup
	for (auto &pair : map) {
		delete pair.second;
	}
}

