#ifndef LEXEM_ANALYZER
#define LEXEM_ANALYZER

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

#include "../entities/Lexem.h"
#include "../entities/Ident.h"
#include "../entities/TableIdent.h"

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
	bool analyze();

	std::vector<Lexem> &getLexems();
	TableIdent &getTable();
	std::string &getString();
	void printLexems() const;
	void printTable() const;
};


#endif