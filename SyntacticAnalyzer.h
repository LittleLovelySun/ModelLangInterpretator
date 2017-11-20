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
	void Analyze(size_t ind = 0);

};

#endif