#include "config.h"
#include "pass1.h"
#include "pass2.h"


int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " source.asm object.obj" << endl;
		exit(0);
	}

	ifstream input(argv[1]);
	if (!input.is_open()) {
		cerr << "Source file can't be opened" << endl;
		return 1;
	}
	
	cout << endl << "Pass 1 start" << endl << endl;

	if (!pass1(input)) {
		cerr << "Error occurs during pass 1" << endl;
		input.close();
		return 1;
	}
	input.close();

	cout << endl << "Pass 1 end" << endl;

	ofstream output(argv[2]);
	if (!output.is_open()) {
		cerr << "Object file can't be opened" << endl;
		return 1;
	}

	cout << endl << "Pass 2 start" << endl << endl ;
	if (!pass2(output)) {
		cerr << "Error occurs during pass 2" << endl;
		output.close();
		return 1;
	}
	cout << endl << "Pass 2 end" << endl;

	output.close();

	return 0;
}