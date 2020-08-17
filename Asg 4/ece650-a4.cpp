#include <iostream>
#include "UserInput.h"

using namespace std;

int main() {

	try {
		UserInput input_obj;
		input_obj.getInput();
	}
	catch (exception & e) {
		cerr << "Error: " << endl;
	}
	return 0;
}