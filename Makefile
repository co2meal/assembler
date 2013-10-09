all: assembler

assembler: main.cpp optable.cpp pass1.cpp pass2.cpp util.cpp
	g++ -o assembler main.cpp optable.cpp pass1.cpp pass2.cpp util.cpp
