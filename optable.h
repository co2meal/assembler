#ifndef __OPTABLE_H__
#define __OPTABLE_H__

#include <string>
#include <map>

using namespace std;

struct instruction {
	int opcode;
	int format;

	instruction(){}
	instruction(int format, int opcode) {
		this->format = format;
		this->opcode = opcode;
	}
};

class Optable{
	static Optable* instance;
	
public:
	map<string, instruction> instructions;


	static Optable* getInstance() {
		if (instance == NULL) {
			instance = new Optable();

			instance->instructions["ADD"]     = instruction(3, 0x18);
			instance->instructions["ADDF"]    = instruction(3, 0x58);
			instance->instructions["ADDR"]    = instruction(2, 0x90);
			instance->instructions["AND"]     = instruction(3, 0x40);
			instance->instructions["CLEAR"]   = instruction(2, 0xB4);
			instance->instructions["COMP"]    = instruction(3, 0x28);
			instance->instructions["COMPF"]   = instruction(3, 0x88);
			instance->instructions["COMPR"]   = instruction(2, 0xA0);
			instance->instructions["DIV"]     = instruction(3, 0x24);
			instance->instructions["DIVF"]    = instruction(3, 0x64);
			instance->instructions["DIVR"]    = instruction(2, 0x9C);
			instance->instructions["FIX"]     = instruction(1, 0xC4);
			instance->instructions["FLOAT"]   = instruction(1, 0xC0);
			instance->instructions["HIO"]     = instruction(1, 0xF4);
			instance->instructions["J"]       = instruction(3, 0x3C);
			instance->instructions["JEQ"]     = instruction(3, 0x30);
			instance->instructions["JGT"]     = instruction(3, 0x34);
			instance->instructions["JLT"]     = instruction(3, 0x38);
			instance->instructions["JSUB"]    = instruction(3, 0x48);
			instance->instructions["LDA"]     = instruction(3, 0x00);
			instance->instructions["LDB"]     = instruction(3, 0x68);
			instance->instructions["LDCH"]    = instruction(3, 0x50);
			instance->instructions["LDF"]     = instruction(3, 0x70);
			instance->instructions["LDL"]     = instruction(3, 0x08);
			instance->instructions["LDS"]     = instruction(3, 0x6C);
			instance->instructions["LDT"]     = instruction(3, 0x74);
			instance->instructions["LDX"]     = instruction(3, 0x04);
			instance->instructions["LPS"]     = instruction(3, 0xD0);
			instance->instructions["MUL"]     = instruction(3, 0x20);
			instance->instructions["MULF"]    = instruction(3, 0x60);
			instance->instructions["MULR"]    = instruction(2, 0x98);
			instance->instructions["NORM"]    = instruction(1, 0xC8);
			instance->instructions["OR"]      = instruction(3, 0x44);
			instance->instructions["RD"]      = instruction(3, 0xD8);
			instance->instructions["RMO"]     = instruction(2, 0xAC);
			instance->instructions["RSUB"]    = instruction(3, 0x4C);
			instance->instructions["SHIFTL"]  = instruction(2, 0xA4);
			instance->instructions["SHIFTR"]  = instruction(2, 0xA8);
			instance->instructions["SIO"]     = instruction(1, 0xF0);
			instance->instructions["SSK"]     = instruction(3, 0xEC);
			instance->instructions["STA"]     = instruction(3, 0x0C);
			instance->instructions["STB"]     = instruction(3, 0x78);
			instance->instructions["STCH"]    = instruction(3, 0x54);
			instance->instructions["STF"]     = instruction(3, 0x80);
			instance->instructions["STI"]     = instruction(3, 0xD4);
			instance->instructions["STL"]     = instruction(3, 0x14);
			instance->instructions["STS"]     = instruction(3, 0x7C);
			instance->instructions["STSW"]    = instruction(3, 0xE8);
			instance->instructions["STT"]     = instruction(3, 0x84);
			instance->instructions["STX"]     = instruction(3, 0x10);
			instance->instructions["SUB"]     = instruction(3, 0x1C);
			instance->instructions["SUBF"]    = instruction(3, 0x5C);
			instance->instructions["SUBR"]    = instruction(2, 0x94);
			instance->instructions["SVC"]     = instruction(2, 0xB0);
			instance->instructions["TD"]      = instruction(3, 0xE0);
			instance->instructions["TIO"]     = instruction(1, 0xF8);
			instance->instructions["TIX"]     = instruction(3, 0x2C);
			instance->instructions["TIXR"]    = instruction(2, 0xB8);
			instance->instructions["WD"]      = instruction(3, 0xDC);
		}
		return instance;
	}
};

#endif __OPTABLE_H__