#include "SyntacticAnalyzer.h"

using namespace std;

SyntacticAnalyzer::SyntacticAnalyzer(const std::vector<Lexem> &lex, const TableIdent &a) {
	for (size_t i = 0; i < lex.size(); i++) 
		lexems.push_back(lex[i]);

	table = a;
}

void SyntacticAnalyzer::Analyze(size_t ind) {
	if (ind == 0 && lexems[ind].getName() != lex_program)
		throw string("Error! The keyword\" program\" is missing!");
}
