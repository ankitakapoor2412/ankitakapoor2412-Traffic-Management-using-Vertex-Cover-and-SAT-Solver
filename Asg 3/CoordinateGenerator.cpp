// BY ANKITA KAPOOR
// Student ID : 20811694
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CoordinatesValidation.h"
#include "CoordinateGenerator.h"

using namespace std;

CoordinateGenerator::CoordinateGenerator() {
	streetInc = 0;
}

vector<int> CoordinateGenerator::getCoord(int numberOfLines, int coordinateRange) {
	int count = 0;
	int limitRandom = 0;
	CoordinatesValidation valid;
	vector<int> coord;
	int numOfLines = generateRandom(1, numberOfLines);
	int totalCoordinates = (numOfLines + 1) * 2;
	while (true) {
		int xCoordinate = generateRandom(coordinateRange * -1, coordinateRange);
		int yCoordinate = generateRandom(coordinateRange * -1, coordinateRange);
		bool r = valid.samePt(coord, xCoordinate, yCoordinate);
		bool r1 = valid.ptInCoordinates(coord, xCoordinate, yCoordinate);
		if (r == 1 && r1 == 1) {
			coord.push_back(xCoordinate);
			coord.push_back(yCoordinate);
			count += 2;
			limitRandom = 0;
		}
		else {
			limitRandom++;
		}
		if (count == totalCoordinates) {
			break;
		}
		if (limitRandom == 25) {
			std::cerr << "Error: Failed in generating the valid inputs for 25 attempts at once." << std::endl;
			exit(1);
		}
	}
	return coord;
}

int CoordinateGenerator::generateRandom(int minValue, int maxValue) {
	if (minValue == maxValue) {
		return minValue;
	}
	else {
		std::ifstream urandom("/dev/urandom");
		if (urandom.fail()) {
			std::cerr << "Error: cannot open /dev/urandom\n";
			return 1;
		}
		unsigned int n = 42;
		urandom.read((char*)&n, sizeof(int));
		urandom.close();
		int numberGenerated = minValue + n%(maxValue - minValue);
		return numberGenerated;
	}
}

vector<string> CoordinateGenerator::makeIn(int numberOfStreets, int numberOfLines, int coordinateRange) {
	vector<string> removeStreet;
	int numOfStreets = generateRandom(2, numberOfStreets);
	for (int m = 0; m < numOfStreets; m++) {
		string coord = "";
		string out = "";
		vector<int> coords = getCoord(numberOfLines, coordinateRange);
		for (unsigned n = 0; n < coords.size() / 2; n++) {
			coord = coord + " (" + to_string(coords[n]) + "," + to_string(coords[n + 1]) + ")";
		}
		string stName = getStName();
		out = "a \"" + stName + "\"" + coord;
		removeStreet.push_back(stName);
		cout << out << endl;
	}
	return removeStreet;
}

string CoordinateGenerator::getStName() {
	string stName = "";
	stName = "Street" + to_string(streetInc);
	streetInc++;
	return stName;
}

void CoordinateGenerator::removeSt(vector<string> removeStreet) {
	for (unsigned p = 0; p < removeStreet.size(); p++) {
		string out = "";
		out = "r \"" + removeStreet[p] + "\"";
		cout << out << endl;
	}

}
