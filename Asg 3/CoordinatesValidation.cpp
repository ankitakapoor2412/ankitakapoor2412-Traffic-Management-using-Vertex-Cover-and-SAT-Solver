// BY ANKITA KAPOOR
// Student ID : 20811694
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "CoordinatesValidation.h"

using namespace std;

double CoordinatesValidation::getDist(int ptx1, int pty1, int ptx2, int pty2) {
	double distx = (ptx2 - ptx1) * (ptx2 - ptx1);
	double disty = (pty2 - pty1) * (pty2 - pty1);
	double dist = sqrt(distx + disty);
	return dist;
}

bool CoordinatesValidation::ptInCoordinates(vector<int> coord, int xCoordinate, int yCoordinate) {
	if (coord.size() >= 6) {
		for (unsigned p = 0; p <= (coord.size()) - 1; p++) {
			double dist = std::floor((getDist(coord[p], coord[p + 1], coord[p + 2], coord[p + 3]) * 100)) / 100;
			double dist1 = std::floor((getDist(coord[p], coord[p + 1], xCoordinate, yCoordinate) * 100)) / 100;
			double dist2 = std::floor((getDist(xCoordinate, yCoordinate, coord[p + 2], coord[p + 3]) * 100)) / 100;
			if (dist1 + dist2 == dist) {
				return false;
			}
			p++;
		}
	}
	return true;
}

bool CoordinatesValidation::samePt(vector<int> coord, int xCoordinate, int yCoordinate) {
	if (coord.size() >= 2) {
		for (unsigned p = 0; p <= (coord.size() - 1); p++) {
			if ((coord[p] == xCoordinate) && (coord[p + 1] == yCoordinate)) {
				return false;
			}
			p++;
		}
	}
	return true;
}
