// BY ANKITA KAPOOR
// Student ID : 20811694
#include <vector>
#include <iostream>
using namespace std;

class CoordinateGenerator {
public:
	int streetInc;
	vector<int> coord;
	CoordinateGenerator();
	vector<int> getCoord(int, int);
	int generateRandom(int, int);
	void removeSt(vector<string>);
	string getStName(void);
	vector<string> makeIn(int, int, int);
};

