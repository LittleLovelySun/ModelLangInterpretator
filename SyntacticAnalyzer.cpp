#include "SyntacticAnalyzer.h"

using namespace std;

SyntacticAnalyzer::SyntacticAnalyzer(const std::vector<Lexem> &lex, const TableIdent &a) {
	lexems = lex;
	table = a;
}

void SyntacticAnalyzer::analyze(size_t ind) {
	if (ind == 0 && lexems[ind].getName() != lex_program)
		throw string("Error! The keyword\" program\" is missing!");
}

void SyntacticAnalyzer::printTable() const {
	cout << "Table:\n" << table;
}