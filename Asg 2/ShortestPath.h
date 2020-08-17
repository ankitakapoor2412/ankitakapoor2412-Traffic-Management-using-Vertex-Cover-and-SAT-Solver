#include <iostream>
#include <list>
#include <vector>

using namespace std;


class ShortestPath {
public:
	list<int>* connect;
	string shortestPath;
	vector<string> getPaths;
	ShortestPath(list<int> vertice);
	void getAdajencyList(list<int> vertice, vector<string> edge);
	void getAllPaths(list<int> vertice, vector<string> edge, int, int);
	void getAllPathUtil(int, int, bool*, int*, int);
	void print_shortestPath();
};