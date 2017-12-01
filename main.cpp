#include "analyzers/LexemAnalyzer.h"
#include "analyzers/SyntacticAnalyzer.h"

#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {
	try {
		std::ifstream f(argv[1]);

		LexemAnalyzer analyzer(f);

		if (!analyzer.analyze())
			return -1;

		std::vector<Lexem> lexems = analyzer.getLexems();

		analyzer.printLexems();
		analyzer.printTable();

		SyntacticAnalyzer a(analyzer.getLexems(), analyzer.getTable(), analyzer.getString());
		if (a.analyze())  {
			std::cout << "Great!" << std::endl;
			a.printTable();
			a.printRPN();
		}
	}
	catch (std::string msg){
		std::cout << msg << std::endl;
	}
}