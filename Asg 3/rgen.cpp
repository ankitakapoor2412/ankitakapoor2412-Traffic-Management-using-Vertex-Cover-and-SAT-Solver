// BY ANKITA KAPOOR
// Student ID : 20811694
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "CoordinateGenerator.h"

using namespace std;

int main(int argc, char** argv) {
	int numOfLines = 5;
	int numOfStreets = 10;
	int waitTime = 5;
	int coordinateRange = 20;
	string numOfLinesStr;
	string numOfStreetsStr;
	string waitTimeStr;
	string coordinateRangeStr;
	vector<string> street = {};
	bool streetFlag = false;
	int i;
	CoordinateGenerator generateIn;
	while ((i = getopt(argc, argv, "s:n:l:c:")) != -1) {
		switch (i)
		{
		case 'c':
			coordinateRangeStr = optarg;
			coordinateRange = atoi(coordinateRangeStr.c_str());
			if (coordinateRange < 1) {
				std::cerr << "Error: This option" << optopt << " is below 5." << std::endl;
				return 1;
			}
			break;
		case 's':
			numOfStreetsStr = optarg;
			numOfStreets = atoi(numOfStreetsStr.c_str());
			if (numOfStreets < 2) {
				std::cerr << "Error: This option" << optopt << " is below 2." << std::endl;
				return 1;
			}
			break;
		case 'n':
			numOfLinesStr = optarg;
			numOfLines = atoi(numOfLinesStr.c_str());
			if (numOfLines < 1) {
				std::cerr << "Error: This option" << optopt << " is below 1." << std::endl;
				return 1;
			}
			break;
		case 'l':
			waitTimeStr = optarg;
			waitTime= atoi(waitTimeStr.c_str());
			if (waitTime < 5) {
				std::cerr << "Error: This option" << optopt << " is below 5." << std::endl;
				return 1;
			}
			break;
		case '?':
			if (optopt == 's' || optopt == 'n' || optopt == 'l' || optopt == 'c')
				std::cerr << "Error: This option" << optopt << " requires an arg." << std::endl;
			else
				std::cerr << "Error: Unknown option: " << optopt << std::endl;
			return 1;
		default:
			return 0;
		}
	}

	waitTime = generateIn.generateRandom(5, waitTime);
	while (true) {
		if (streetFlag) {
			generateIn.removeSt(street);
		}
		street = generateIn.makeIn(numOfStreets, numOfLines, coordinateRange);
		cout << "g" << endl;
		streetFlag = true;
		sleep(waitTime);
	}
	return 0;
}
