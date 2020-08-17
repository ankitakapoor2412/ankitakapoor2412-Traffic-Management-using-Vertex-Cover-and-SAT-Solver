// BY ANKITA KAPOOR
// Student ID : 20811694
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "UserInput.h"
#include "ShortestPath.h"

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
			cout << input << endl;
			int verticeRange = atoi(input.substr(2, input.length()).c_str());
			for (int i = 0; i < verticeRange; i++) {
				vertice.push_back(i);
			}
			edge.clear();
		}
		else if (input[0] == 'E' && input[1] == ' ') {
			cout << input << endl;
			if (vertice.size() > 1 && edge.size() == 0) {
				bool flag = false;
				for (unsigned i = 0; i < input.length(); i++) {
					if (input[i] == '<') {
						string st = "";
						while (input[i] != '>') {
							if (input[i] != ',') {
								st = st + input[i];
								i++;
							}
							else {
								st = st.substr(1, st.length());
								int val = atoi(st.c_str());
								list<int>::iterator itr;
								itr = std::find(vertice.begin(), vertice.end(), val);
								if (itr == vertice.end()) {
									std::cerr << "Error: Incorrect Input of edges.\n";
									edge.push_back(st);
									flag = true;
									vertice.clear();
									break;
								}
								else {
									edge.push_back(st);
								}
								i++;
								st = "";
							}
						}
						if (flag == true) {
							break;
						}
						else {
							int val = atoi(st.c_str());
							list<int>::iterator itr;
							itr = find(vertice.begin(), vertice.end(), val);
							if (itr == vertice.end()) {
								std::cerr << "Error: Incorrect Input of edges.\n";
								flag = true;
								vertice.clear();
								break;
							}
							else {
								edge.push_back(st);
							}
						}
					}
				}
			}
			else {
				std::cerr << "Error: Edges are already present or Vertices not found for the given edges.\n";
				vertice.clear();
			}
		}
		else if (input[0] == 's') {
			if (edge.size() >= 1 && vertice.size() > 1) {
				vector<string> element = getSrcAndDes(input);
				int src = atoi(element[1].c_str());
				int des = atoi(element[2].c_str());
				list<int>::iterator itsrc;
				itsrc = std::find(vertice.begin(), vertice.end(), src);
				list<int>::iterator itdes;
				itdes = std::find(vertice.begin(), vertice.end(), des);
				if (itsrc == vertice.end() || itdes == vertice.end()) {
					std::cerr << "Error: No Src or Destination found in vertices.\n";
				}
				else {
					ShortestPath sp_obj(vertice);
					sp_obj.getAllPaths(vertice, edge, src, des);
					sp_obj.print_shortestPath();
					sp_obj.getPaths.clear();
				}
			}
			else {
				std::cerr << "Error: Edges or Vertices not found for the given input.\n";
				vertice.clear();
			}
		}
		else {
			std::cerr << "Error: Invalid Input!\n";
		}
	}
}

vector<string> UserInput::getSrcAndDes(string input) {
	istringstream is_stream(input);
	vector<string> op;
	while (is_stream)
	{
		string subst;
		is_stream >> subst;
		op.push_back(subst);
	}
	return op;
}