#include <algorithm>
#include <vector>
#include <memory>
#include "minisat/core/Solver.h"
#include "minisat/core/SolverTypes.h"
#include "VertexCover.h"

using namespace std;


void VertexCover::minVertexCov(int numOfVertices, int numOfEdges, vector<string> edge) {
	bool stopp = true;
	vector<int> final_litrals = {};
	int min = 1;
	while (stopp || (min == (numOfVertices + 1))) {
		unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
		vector<int> litralIndex = {};
		int atom = min * numOfVertices;
		Minisat::vec<Minisat::Lit> litrals;
		for (int i = 0; i < atom; i++) {
			Minisat::Lit ml = Minisat::mkLit(solver->newVar());
			litrals.push(ml);
		}
		for (int i = 0; i < min; i++) {
			Minisat::vec<Minisat::Lit> clause_add;
			for (int j = 0; j < numOfVertices; j++) {
				int position = (i + (min * j));
				litralIndex.push_back(position);
				clause_add.push(litrals[position]);
			}
			solver->addClause(clause_add);
		}
		int negLiterals = numOfVertices + (combi(numOfVertices) * 2);
		vector<int> negCombinations = negCombi(negLiterals, litralIndex, numOfVertices, min);
		for (unsigned i = 0; i < negCombinations.size();) {
			Minisat::vec<Minisat::Lit> clause_add;
			clause_add.push(~litrals[negCombinations.at(i)]);
			clause_add.push(~litrals[negCombinations.at(i + 1)]);
			solver->addClause(clause_add);
			i = i + 2;
		}
		for (unsigned i = 0; i < edge.size();) {
			Minisat::vec<Minisat::Lit> clause_add;
			for (int j = 0; j < min; j++) {
				clause_add.push(litrals[litralIndex.at(atoi(edge.at(i).c_str()) + (j * numOfVertices))]);
				clause_add.push(litrals[litralIndex.at(atoi(edge.at(i + 1).c_str()) + (j * numOfVertices))]);
			}
			solver->addClause(clause_add);
			i = i + 2;
		}
		bool resol = solver->solve();
		if (resol == 1) {
			final_litrals.empty();
			vector<int> vertexCov = {};
			stopp = false;
			for (int i = 0; i < atom; i++) {
				final_litrals.push_back(Minisat::toInt(solver->modelValue(litrals[i])));
			}
			for (unsigned i = 0; i < final_litrals.size(); i++) {
				if (final_litrals.at(i) == 0) {
					vertexCov.push_back(i / min);
				}
			}
			sort(vertexCov.begin(), vertexCov.end());
			for (unsigned i = 0; i < vertexCov.size(); i++)
				cout << vertexCov.at(i) << " ";
			cout << "" << endl;
		}
		else {
			min++;
		}
	}
}

int VertexCover::combi(int numberOfVertices) {
	return (numberOfVertices * (numberOfVertices - 1)) / 2;
}

vector<int> VertexCover::negCombi(int atoms, vector<int> index, int numberOfVertices, int minimum) {
	vector<int> combinations = {};
	for (int i = 0; i < numberOfVertices; i++) {
		for (int j = i; j < (numberOfVertices * minimum); ) {
			for (int k = j + numberOfVertices; k < (numberOfVertices * minimum);) {
				combinations.push_back(index.at(j));
				combinations.push_back(index.at(k));
				k = k + numberOfVertices;
			}
			j = j + numberOfVertices;
		}
	}
	int c = 0;
	for (unsigned i = 0; i < index.size(); i++) {
		if ((i == 0) || (i % numberOfVertices == 0)) {
			for (unsigned j = i + 1; j < i + numberOfVertices; j++) {
				combinations.push_back(index.at(i));
				combinations.push_back(index.at(j));
			}
			c++;
		}
		else {
			for (int j = i + 1; j < (numberOfVertices * c); j++) {
				combinations.push_back(index.at(i));
				combinations.push_back(index.at(j));
			}
		}
	}
	return combinations;
}