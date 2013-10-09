#include <sstream>
#include <iomanip>
#include "exception.h"
using namespace std;


int StrToInteger(string s) {
	int res;
	stringstream ss;

	ss << s;
	
	ss >> res;
	return res;
}

string DecimalToHex(int i, int w = 0) {
	string res;
	stringstream ss;

	ss << std::hex << setfill('0') << setw(w) << std::uppercase << i;

	ss >> res;
	return res;
}

int HexToInteger(string h) {
	int res;
	stringstream ss;

	ss << h;

	ss >> std::hex >> res;

	return res;
}


int LengthOfConstant(string s) throw (exception) {
	int len = 0;
	bool opened = false;

	if (s.length() < 2) throw invalid_constant_exception();

	for(int i=1;i<s.length();i++) {
		if (s[i] == '\'') {
			opened = !opened;
			continue;
		}
		if (opened) {
			len ++;
		} else throw invalid_constant_exception();
	}

	if (opened) throw invalid_constant_exception();

	if (s[0] == 'X') {
		if (len % 2) throw invalid_constant_exception();
		len /= 2;
	} else if (s[0] != 'C') throw invalid_constant_exception();


	return len;
}

string BytesOfConstant(string s) throw (exception) {
	string result;
	bool opened = false;

	if (s.length() < 2) throw invalid_constant_exception();

	for(int i=1;i<s.length();i++) {
		if (s[i] == '\'') {
			opened = !opened;
			continue;
		}
		if (opened) {
		} else throw invalid_constant_exception();
	}
	if (opened) throw invalid_constant_exception();

	if (s[0] == 'X') {
		result = s.substr(2, s.length() - 3);
	} else if (s[0] == 'C') {
		for (int i=2;i<s.length()-1;i++) {
			result += DecimalToHex(s[i], 2);
		}
	} else throw invalid_constant_exception();

	return result;
}