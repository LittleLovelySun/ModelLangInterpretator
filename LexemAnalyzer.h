#ifndef LEXEM_ANALYZER
#define LEXEM_ANALYZER

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Lexem.h"
#include "Ident.h"
#include "TableIdent.h"

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