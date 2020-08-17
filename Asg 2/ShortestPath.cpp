#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <iterator>
#include <stdlib.h>
#include "ShortestPath.h"

using namespace std;


ShortestPath::ShortestPath(list<int> vertice) {
	connect = new list<int>[vertice.size()];
}

void ShortestPath::getAllPaths(list<int> vertice, vector<string> edge, int src, int des) {
	getAdajencyList(vertice, edge);
	int num_vertices = vertice.size();
	int* p = new int[num_vertices];
	int p_index = 0;
	bool* visited = new bool[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		visited[i] = false;
	}
	ShortestPath::getAllPathUtil(src, des, visited, p, p_index);
}

void ShortestPath::getAdajencyList(list<int> vertice, vector<string> edge) {
	int num_edges = edge.size() - 1;
	int eStart, eEnd;
	for (int i = 0; i < num_edges; i++) {
		eStart = atoi(edge[i].c_str());
		eEnd = atoi(edge[i + 1].c_str());
		connect[eStart].push_back(eEnd);
		connect[eEnd].push_back(eStart);
		i++;
	}
}

void ShortestPath::getAllPathUtil(int src, int des, bool visited[], int p[], int p_index) {
	visited[src] = true;
	p[p_index] = src;
	p_index++;
	if (src == des)
	{
		string st = "";
		for (int i = 0; i < p_index; i++) {
			st = st + to_string(p[i]) + "-";
		}
		st = st.substr(0, st.size() - 1);
		if (st.size() == 1) {
			getPaths.push_back(st+"-"+st);
		}
		else {
			getPaths.push_back(st);
		}
	}
	else
	{
		list<int>::iterator i;
		for (i = connect[src].begin(); i != connect[src].end(); ++i) {
			if (!visited[*i]) {
				getAllPathUtil(*i, des, visited, p, p_index);
			}
		}
	}
	p_index--;
	visited[src] = false;
}

void ShortestPath::print_shortestPath() {
	int maximum = 0;
	if (getPaths.size() > 0) {
		for (unsigned i = 0; i < getPaths.size(); i++) {
			int count = 0;
			for (unsigned j = 0; j < getPaths[i].length(); j++) {
				if (getPaths[i][j] == '-') {
					count++;
				}
			}
			if ((i == 0) || (count < maximum)) {
				maximum = count;
				shortestPath = getPaths[i];
			}
		}
	}
	else {
		cout << "Error : No Path found between the given nodes.";
	}
		cout << shortestPath << endl;
}