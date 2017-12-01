#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../entities/Lexem.h"
#include "../entities/Ident.h"
#include "../entities/TableIdent.h"

std::string typeToString(IdentT type);

class SyntacticAnalyzer {
	std::string in;
	size_t ind;
	std::vector<Lexem> rpn;
	std::vector<Lexem> lexems;
	TableIdent table;

	Lexem &currLex();
	Lexem &nextLex();
	Lexem &prevLex();

	void parse();

	void parseWhile();
	void parseDoWhile();
	void parseIf();
	void parseFor();
	void parseRead();
	void parseWrite();
	void parseAsign(bool needSemicolon = true);

	IdentT parseExpression();
	IdentT term();
	IdentT term1();
	IdentT entity();

	IdentT parseIdent();

	std::string getString(bool prev = false);


	void parseDeclaration(IdentT type);

	IdentT checkTypes(IdentT leftType, Lexem sign, IdentT rightType);
public:
	SyntacticAnalyzer(const std::vector<Lexem> &lex, const TableIdent &tab, const std::string input);
	bool analyze();
	void printTable() const;
	void printRPN() const;
};