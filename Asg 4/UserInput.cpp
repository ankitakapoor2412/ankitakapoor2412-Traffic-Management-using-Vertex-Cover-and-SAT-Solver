#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "UserInput.h"
#include "VertexCover.h"
#include<bits/stdc++.h>

using namespace std;


void UserInput::getInput() {
	while (true) {
		string input = "";
		getline(cin, input);
		if (!cin || input == "") {
			if (cin.eof()) {
				break;
			}
			else {
				break;
			}
		}
		else if (input[0] == 'V') {
			vertice.clear();
			int verticeRange = atoi(input.substr(2, input.length()).c_str());
			for (int i = 0; i < verticeRange; i++) {
				vertice.push_back(i);
			}
			edge.clear();
		}
		else if (input[0] == 'E' && input[1] == ' ') {
			if (vertice.size() > 1) {
				if (validateEdge(input) == 0) {
					if (edge.size() > 0) {
						VertexCover find_vertex;
						find_vertex.minVertexCov(vertice.size(), edge.size(), edge);
					}
					else {
						cout << "Error: There exists no vertex cover." << endl;
					}
				}
			}
			else {
				cout << "Error: Vertices not found for the given input.\n";
				vertice.clear();
			}
		}
		else {
			cout << "Error: Invalid Input!\n";
		}
	}
}

int UserInput::validateEdge(string input) {
	if (!regex_match(input, std::regex("^[E]\\s\\{\\}$"))) {
		if (regex_match(input, std::regex("^[E]\\s\\{[\\<\\d+\\,\\d+\\>\\,]*\\<\\d+\\,\\d+\\>\\}$"))) {
			for (unsigned m = 0; m < input.length(); m++) {
				if (input[m] == '<') {
					string st = "";
					while (input[m] != '>') {
						if (input[m] != ',') {
							st = st + input[m];
							m++;
						}
						else {
							st = st.substr(1, st.length());
							int val = atoi(st.c_str());
							list<int>::iterator itr;
							itr = std::find(vertice.begin(), vertice.end(), val);
							if (itr == vertice.end()) {
								cout << "Error: Incorrect Input of edges." << endl;
								edge.push_back(st);
								vertice.clear();
								return 1;
							}
							else {
								edge.push_back(st);
							}
							m++;
							st = "";
						}
					}
					int val = atoi(st.c_str());
					list<int>::iterator itr;
					itr = find(vertice.begin(), vertice.end(), val);
					if (itr == vertice.end()) {
						cout << "Error: Incorrect Input of edges." << endl;
						vertice.clear();
						return 1;
					}
					else {
						edge.push_back(st);
					}
				}
			}
		}
		else {
			cout << "Error: Incorrect Input of edges." << endl;
			return 1;
		}
	}
	else {
		cout << "There exists no vertex cover." << endl;
		return 1;
	}

	return 0;
}