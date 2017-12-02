#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include "../entities/Lexem.h"
#include "../entities/Ident.h"
#include "../entities/TableIdent.h"
#include "../entities/Enum.h"

class Executor {
	std::vector<Lexem> rpn;
	size_t ind;
	TableIdent table;
	std::stack<Lexem> stack;

	void executeKeyword();
	void executeAriphmetic();
	void executeShortOp();
	void executeComparison();

	double LtoD(Lexem &lex);
	double LtoD(Ident *ident);
public:
	Executor(const std::vector<Lexem> &rpn, const TableIdent &table);
	void execute();
};