#include "LexemAnalyzer.h"
#include "SyntacticAnalyzer.h"

#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::ifstream f("tests/test1.sunProg");

	LexemAnalyzer analyzer(f);

	analyzer.analyze();

	std::vector<Lexem> lexems = analyzer.getLexems();

	analyzer.printLexems();
	analyzer.printTable();

	SyntacticAnalyzer a();
}