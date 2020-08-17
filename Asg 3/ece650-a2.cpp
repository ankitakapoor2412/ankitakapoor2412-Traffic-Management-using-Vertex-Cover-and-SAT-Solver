// BY ANKITA KAPOOR
// Student ID : 20811694
#include <iostream>
#include "UserInput.h"

using namespace std;


int main(int argc, char** argv) {

	try {
		UserInput in_obj;
		in_obj.getInput();
	}
	catch (exception & e) {
		std::cerr << "Error: From main\n";
	}
	return 0;
}