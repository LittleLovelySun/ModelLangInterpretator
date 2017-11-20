#ifndef SYNTACTIC
#define SYNTECTIC

#include <iostream>
#include <vector>
#include <string>

#include "Lexem.h"
#include "Ident.h"
#include "TableIdent.h"


class SyntacticAnalyzer {
	std::vector<Lexem> lexems;
	TableIdent table;

public:
	SyntacticAnalyzer(const std::vector<Lexem> &lex, const TableIdent &tab);
	void analyze(size_t ind = 0);

	//void printLexems() const;
	void printTable() const;

};

#endif