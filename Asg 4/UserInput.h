#include <iostream>
#include <list>
#include <vector>

using namespace std;


class UserInput {
public:
	void getInput();
	list<int> vertice;
	vector<string> edge;
	int validateEdge(string);
};