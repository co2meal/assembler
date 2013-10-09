#include "config.h"
#include <iomanip>
using namespace std;

void write_text_record(ofstream& output, string& buffer, int locctr, string objcode);
void flush_text_record(ofstream& output, string& buffer);


bool pass2(ofstream& output) throw() {
	string output_buffer;
	bool result = true;
	vector<string> codes;

	map<string, int> symbol_table;
	map<string, int>::iterator sym_it;
	
	string progname;
	int proglen;

	ifstream input(IMMEDIATE_FILE);
	
	string line;

	while(getline(input, line)) {
		if (line == "") break;

		codes.push_back(line);
	}

	while(getline(input, line)) {
		if (line == "") break;
		string label;
		int locctr;
		stringstream ss(line);

		ss >> label >> std::hex >> locctr;

		symbol_table[label] = locctr;
	}

	while(getline(input, line)) {
		string key, val;
		stringstream ss(line);

		ss >> key >> val;
		
		if (key == "progname")
			progname = val;
		else if (key == "proglen")
			proglen = HexToInteger(val);
		//else if (key == "startloc")
		//	startloc = HexToInteger(val);
	}



	for(int i=0;i < codes.size(); i++) {
		string& line = codes[i];
		stringstream ss(line);

		int locctr;
		string mnemonic, operand;
		string objcode;
		string error;

		try {
			ss >> std::hex >> locctr >> mnemonic >> operand;


			Optable* optable = Optable::getInstance();
			map<string, instruction>::iterator op_it;

			if ((op_it = optable->instructions.find(mnemonic)) != optable->instructions.end()) {
				objcode += DecimalToHex(op_it->second.opcode, 2);

				if (operand.length() > 0) {
					bool x = false;
					if (operand.rfind(",X") == operand.length() - 2) {
						x = true;
						operand = operand.substr(0, operand.length() - 2);
					}

					map<string, int>::iterator it;

					if ((it = symbol_table.find(operand)) != symbol_table.end()) {
						objcode += DecimalToHex((x << 15) | it->second, 4);
					} else {
						cout << "Undefined symbol error" << endl;
					}
				} else {
					objcode += DecimalToHex(0x0000, 4);
				}

			

			} else if (mnemonic == "START") {
				output.setf(ios::left);
				output << "H" << setw(6) << progname << DecimalToHex(HexToInteger(operand), 6) << DecimalToHex(proglen, 6) << endl;
				continue;
			} else if (mnemonic == "WORD") {
				objcode = DecimalToHex(StrToInteger(operand), 6);
			} else if (mnemonic == "RESW") {
				flush_text_record(output, output_buffer);
			} else if (mnemonic == "RESB") {
				flush_text_record(output, output_buffer);
			} else if (mnemonic == "BYTE") {
				objcode = BytesOfConstant(operand);
			} else if (mnemonic == "END") {
				flush_text_record(output, output_buffer);

				if((sym_it = symbol_table.find(operand)) != symbol_table.end()) {
					output << "E" << DecimalToHex(sym_it->second, 6) << endl;
				} else {
					throw undefined_symbol_exception();
				}
				break;
			} else {
				throw invalid_operator_exception();
			}
		} catch (const exception& ex) {
			error = ex.what();
			result = false;
		}
		
		cout << mnemonic << "\t" << operand << "\t" << objcode << "\t" << error << endl;
		write_text_record(output, output_buffer, locctr, objcode);
	}



	input.close();

	return result;
}

void write_text_record(ofstream& output, string& buffer, int locctr, string objcode) {
	if (objcode == "") return;

	if (buffer.length() + objcode.length() > 60) flush_text_record(output, buffer);

	if(buffer.length() == 0) output << "T" << DecimalToHex(locctr, 2);
	buffer += objcode;

}

void flush_text_record(ofstream& output, string& buffer) {
	if (buffer.length() == 0) return;

	output << DecimalToHex(buffer.length(), 2) << buffer << endl;
	buffer = "";
}