#ifndef LEXEM_ANALYZER
#define LEXEM_ANALYZER

#include "Lexemes.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>



class LexemAnalyzer {
	std::string in;
	std::vector<Lexem> lexems;
	TableIdent table;

	bool isDigit(char c);
	bool isLetter(char c);
	bool isLikeDelimeter(char c);
public:
	LexemAnalyzer(const std::string &in);
	LexemAnalyzer(std::ifstream &input);
	void analyze();

	std::vector<Lexem> &getLexems();
	void printLexems() const;
	void printTable() const;
};


#endif