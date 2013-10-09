#include "config.h"

using namespace std;


bool pass1(ifstream& input) throw() {
	int locctr = -1;
	string line;
	bool result = true;
	map<string, int> symbol_table;
	map<string, int>::iterator sym_it;

	string progname;
	int startaddr = 0;
	int proglen = 0;

	ofstream output(IMMEDIATE_FILE);

	while(getline(input, line)) {
		stringstream ss(line);
		string label, mnemonic, operand, comment, error;
		int next_locctr;

		try {
			if (line.length() > 0 && line[0] == '.') {
				continue;
			}
			if (line.length() > 0 && isalpha(line[0])) ss >> label;
			ss >> mnemonic >> operand;
			getline(ss, comment);
			for(int i=0;i<comment.length();i++) if (isalpha(comment[i])) {
				comment.erase(0, i);
				break;
			}

			map<string, instruction>::iterator op_it;
			Optable* optable = Optable::getInstance();

			if ((op_it = optable->instructions.find(mnemonic)) != optable->instructions.end()) {
				next_locctr = locctr + 3;
			} else if (mnemonic == "START") {
				next_locctr = HexToInteger(operand);
				locctr = next_locctr;
				progname = label;
				startaddr = locctr;
			} else if (mnemonic == "WORD") {
				next_locctr = locctr + 3;
			} else if (mnemonic == "RESW") {
				next_locctr = locctr + 3 * StrToInteger(operand);
			} else if (mnemonic == "RESB") {
				next_locctr = locctr + StrToInteger(operand);
			} else if (mnemonic == "BYTE") {
				next_locctr = locctr + LengthOfConstant(operand);
			} else if (mnemonic == "END") {
				proglen = locctr - startaddr;
				next_locctr = locctr;
			} else {
				throw invalid_operator_exception();
			}

			if (label.length() > 0) {
				if (symbol_table.find(label) != symbol_table.end()) {
					throw duplicated_symbol_exception();
				} else {
					symbol_table[label] = locctr;
				}
			}

		} catch (const exception& ex) {
			error = ex.what();
			next_locctr = locctr;
			result = false;
		}
		
		cout   << DecimalToHex(locctr) << "\t" << label << "\t" << mnemonic << "\t" << operand << "\t" << comment << "\t" << error << endl;
		output << DecimalToHex(locctr) << "\t" << mnemonic << "\t" << operand << endl;

		locctr = next_locctr;
	}
	
	output << endl;

	for(sym_it = symbol_table.begin(); sym_it != symbol_table.end(); sym_it++) {
		output << sym_it->first << "\t" << DecimalToHex(sym_it->second) << endl;
	}

	output << endl;
	
	output << "progname\t" << progname << endl;
	output << "proglen\t"  << DecimalToHex(proglen) << endl;

	output.close();

	return result;
}