#include "SyntacticAnalyzer.h"

using namespace std;


Lexem& SyntacticAnalyzer::currLex() {
	return lexems[ind];
}

Lexem& SyntacticAnalyzer::nextLex() {
	ind++;
	return lexems[ind];
}

Lexem& SyntacticAnalyzer::prevLex() {
	ind--;
	return lexems[ind];
}

SyntacticAnalyzer::SyntacticAnalyzer(const std::vector<Lexem> &lex, const TableIdent &a, const std::string input) {
	ind = 0;
	lexems = lex;
	table = a;
	in = input;
}



bool SyntacticAnalyzer::analyze() {
	try {
		if (!lexems[0].check(lex_program))
			throw string("Missing keyword 'program'!");

		if (!lexems[1].check(lex_lbrace))
			throw string("Missing '{' an the beginning of program!");

		if (!lexems[lexems.size() - 1].check(lex_rbrace))
			throw string("Missing '}' an the ending of program!");


		lexems.erase(lexems.end() - 1);
		lexems.erase(lexems.begin());
		lexems.erase(lexems.begin());

		while (currLex().isData()) 
			parseDeclaration(currLex().getIdentT());

		while (ind < lexems.size())
			parse();

	} catch (string msg) {
		cout << "Expresions: " << msg << std::endl;
		return false;
	}

	return true;
}


void SyntacticAnalyzer::parse() {
	if (currLex().check(lex_while)) {
		parseWhile();
	}

	else if (currLex().check(lex_do)) {
		parseDoWhile();
	}

	else if (currLex().check(lex_if)) {
		parseIf();
	}

	else if (currLex().check(lex_for)) {
		parseFor();
	}

	else if (currLex().check(lex_read)) {
		parseRead();
	}

	else if (currLex().check(lex_write)) {
		parseWrite();
	}

	else if (currLex().check(LexemT::ident)) {
		parseAsign();
	}
	
	else if (currLex().check(lex_lbrace)) {
		nextLex();

		while (!currLex().check(lex_rbrace))
			parse();
		
		nextLex();
	}
	else if (currLex().check(lex_semicolon)) {
		nextLex();
	}
	else 
		throw ("Unexpexted symbol '") + currLex().getName() + "'!";
}


void SyntacticAnalyzer::parseDeclaration(IdentT type) {
	do {
		nextLex();
		if (!currLex().check(LexemT::ident)) 
			throw string("Incorrect declaration") + currLex().getName();	

		Ident* tmp = table.getByName(currLex().getName());

		if (tmp->getDec())
			throw string("Identifier '") + tmp->getName() + string("' was already declared");

		tmp->setType(type);
		tmp->setAsDefault();
		tmp->setDec(true);

		nextLex();

		if (currLex().check(lex_asign)) {
			nextLex();
			if (currLex().check(LexemT::ident)) {
				Ident *t = table.getByName(currLex().getName());
				if (!t->getDec())
					throw string("Identifier '") + t->getName() + string("' is not declared");

				if (type != t->getType()) 
					throw string("Identifieres '") + tmp->getName() +"' and '" + t->getName() + string("' have different types");
				tmp->setValue(t->getValue());
			}
			
			else if (currLex().isConst() || currLex().check(lex_minus)) {
				bool sign = currLex().check(lex_minus);
				if (sign) {
					if (!(type == IdentT::type_int || type == IdentT::type_real))
						throw string("Symbol '-' with type can't be used with string or bool identifieres");

					nextLex();
					currLex().setName(lex_minus + currLex().getName());
				}
					
				if (type != currLex().getIdentT())
					throw string("Constant value '") + currLex().getName() + "' and '" + tmp->getName() + "' have different types in line: " + getString();

				tmp->setValue(currLex().getName());
			}
			else
				throw string("Identifier or constatnt value expected!");

			nextLex();
		}
		
	} while (currLex().check(lex_comma));

	if (!currLex().check(lex_semicolon)) 
		throw string("Incorrect symbol ") + currLex().getName() + " in declaration in line: " + getString();
	
	nextLex();
}


//****************************************************************************************************************************************************//


IdentT SyntacticAnalyzer::checkTypes(IdentT left, Lexem sign, IdentT right) {
	if (sign.isAriphmetic()) {
		if (left == IdentT::type_int && right == IdentT::type_int)
			return IdentT::type_int;

		if ((left == IdentT::type_real || left == IdentT::type_int) && (right == IdentT::type_real || right == IdentT::type_int) && sign.check(lex_mod))
			return IdentT::type_real;

		if (left == IdentT::type_string && right == IdentT::type_string && sign.check(lex_plus))
			return IdentT::type_string;	

		throw string("'") + sign.getName() + "' incompatible with given types ('" + typeToString(left) + "' and '" + typeToString(right) + "') in line " + 	to_string(currLex().getLineNum()) + "\n" + getString();
	}

	if (sign.isComparison()) {
		if (((left == IdentT::type_real || left == IdentT::type_int) && (right == IdentT::type_real || right == IdentT::type_int)) ||
			(left == IdentT::type_bool && right == IdentT::type_bool) || (left == IdentT::type_string && right == IdentT::type_string))
			return IdentT::type_bool;

		throw string("'") + sign.getName() + "' incompatible with given types ('" + typeToString(left) + "' and '" + typeToString(right) + "') in line " + 	to_string(currLex().getLineNum()) + "\n" + getString();
	}

	if (sign.getName() == lex_or || sign.getName() == lex_and) {
		if ((left == IdentT::type_bool && right == IdentT::type_bool)) 
			return IdentT::type_bool;

		throw string("Logic operation can be applay onle with bool type! ") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();
	}

	throw string("Unknown sign '") + sign.getName() + "'' in operation in line " + to_string(currLex().getLineNum()) + "\n" + getString();
}

IdentT SyntacticAnalyzer::parseIdent() {
	Ident* tmp = table.getByName(currLex().getName());

	if (tmp == nullptr) 
		throw string("'") + currLex().getName() + "' is not identifiere"; 

	if (!tmp->getDec())
		throw string("Identifier '") + currLex().getName() + "' was not declaredin line:" + to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();

	return tmp->getType();
}

string SyntacticAnalyzer::getString(bool prev) {
	string s;
	size_t index = currLex().getInd();

	if (prev) 
		index--;
	
	while (in[index] != '\n' && index < in.length()) {
		s += in[index];
		index++;
	}

	return s;
}

void SyntacticAnalyzer::parseWhile() {
	nextLex();

	if (!currLex().check(lex_lparenthesis)) 
		throw string("Unexpected symbol in 'while'") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();

	size_t conditionLabel = rpn.size(); 

	if (parseExpression() != IdentT::type_bool)
		throw string("Expresion must have bool type in condition") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();

	size_t falseLabel = rpn.size();
	rpn.push_back(Lexem(LexemT::rpn_label, "-1"));
	rpn.push_back(Lexem(LexemT::rpn_fgo, ""));

	if (!currLex().check(lex_rparanthesis))
		throw string("Unexpected symbol in 'while'") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();
	parse();

	rpn.push_back(Lexem(LexemT::rpn_label, to_string(conditionLabel)));
	rpn.push_back(Lexem(LexemT::rpn_go, ""));

	rpn[falseLabel].setName(to_string(rpn.size()));
}

void SyntacticAnalyzer::parseDoWhile() {
	nextLex();

	size_t doLabel = rpn.size();

	parse(); 

	if (!currLex().check(lex_while)) 
		throw string("Missing 'while' in 'do..while'") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();
	nextLex();

	if (!currLex().check(lex_lparenthesis))
		throw string("Missing '(' in expression") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();

	if (parseExpression() != IdentT::type_bool)
		throw string("Expresion can be only bool in condition") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();

	if (!currLex().check(lex_rparanthesis))
		throw string ("Uncapped bracket") + " line:" + to_string(currLex().getLineNum()) + "\n" + getString();

	size_t falseLabel = rpn.size();
	rpn.push_back(Lexem(LexemT::rpn_label, ""));
	rpn.push_back(Lexem(LexemT::rpn_fgo, ""));

	nextLex();

	//TODO: checkDelimeter(lex_semicolon);
	if (!currLex().check(lex_semicolon))
		throw string ("Missing ';' in line:")+ to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();

	rpn.push_back(Lexem(LexemT::rpn_label, to_string(doLabel)));
	rpn.push_back(Lexem(LexemT::rpn_go, ""));

	rpn[falseLabel].setName(to_string(rpn.size()));
}

void SyntacticAnalyzer::parseIf() {
	nextLex();

	if (!currLex().check(lex_lparenthesis))
		throw string("Missing '(' in line ") + to_string(currLex().getLineNum()) + getString(); // no tut ze prosto skobka propushena

	nextLex();

	if (parseExpression() != IdentT::type_bool)
		throw string("Expresion can be only bool in condition in line ") + to_string(currLex().getLineNum()) + getString();
	
	size_t labelIf = rpn.size();

	rpn.push_back(Lexem(LexemT::rpn_label, "-1"));
	rpn.push_back(Lexem(LexemT::rpn_fgo, ""));
	
	if (!currLex().check(lex_rparanthesis))
		throw string ("Uncapped bracket in line ") + to_string(currLex().getLineNum()) + getString();

	nextLex();

	parse();

	rpn[labelIf].setName(to_string(rpn.size()));

	if (currLex().check(lex_else)) {
		size_t  labelElse = rpn.size();

		rpn.push_back(Lexem(LexemT::rpn_label, "-1"));
		rpn.push_back(Lexem(LexemT::rpn_go, ""));
		rpn[labelIf].setName(to_string(rpn.size()));
		
		nextLex();
		parse();	

		rpn[labelElse].setName(to_string(rpn.size()));
	}
}

void SyntacticAnalyzer::parseFor() {
	nextLex();

	if (!currLex().check(lex_lparenthesis))
		throw string("Unexpected symbol in expression in line ")+ to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();

	if (!currLex().check(lex_semicolon)) 
		parseAsign();
	else
		nextLex();

	size_t beginLable = rpn.size();

	if (!currLex().check(lex_semicolon)) {
		if (parseExpression() != IdentT::type_bool)
			throw string("Expresion can be only bool in condition in line ") + to_string(currLex().getLineNum()) + "\n" + getString();

		if (!currLex().check(lex_semicolon))
			throw string ("Missing ';' ") + getString();
	}

	size_t falseLabel = rpn.size();

	rpn.push_back(Lexem(LexemT::rpn_label, "-1"));
	rpn.push_back(Lexem(LexemT::rpn_fgo, ""));

	nextLex();

	if (!currLex().check(lex_rparanthesis)) 
		parseAsign(false);

	
	if (!currLex().check(lex_rparanthesis))
		throw string ("Uncapped bracketin line ") + to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();
	parse();

	rpn.push_back(Lexem(LexemT::rpn_label, to_string(beginLable)));
	rpn.push_back(Lexem(LexemT::rpn_go, ""));

	rpn[falseLabel].setName(to_string(rpn.size()));
}

void SyntacticAnalyzer::parseRead() {
	nextLex();

	if (!currLex().check(lex_lparenthesis))
		throw string("Missing '(' in 'read'in line ") + to_string(currLex().getLineNum()) + "\n" + getString();

	do {
		string address = nextLex().getName();
		parseIdent();
		rpn.push_back(Lexem(LexemT::rpn_address, address));
		rpn.push_back(Lexem(LexemT::keyword, lex_read));
	} while (currLex().check(lex_comma));

	if (!currLex().check(lex_rparanthesis))
		throw string ("Uncapped bracketin line ") + to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();

	if (!currLex().check(lex_semicolon))
		throw string ("Missing ';' in line: ") + to_string(currLex().getLineNum()) + "\n" + getString();

	nextLex();
}

void SyntacticAnalyzer::parseWrite() {
	nextLex();

	if (!currLex().check(lex_lparenthesis))
		throw string("Missing '(' in 'read' in line ") + to_string(currLex().getLineNum()) + "\n" + getString();

	do {
		nextLex();
		parseExpression();
		rpn.push_back(Lexem(LexemT::keyword, lex_write));
	} while (currLex().check(lex_comma));



	if (!currLex().check(lex_rparanthesis))
		throw string ("Uncapped bracketin line ") + "\n" + getString();

	nextLex();
	if (!currLex().check(lex_semicolon))
		throw string ("Missing ';' in line: \n") + getString();

	nextLex();
}

IdentT SyntacticAnalyzer::parseExpression() {
	IdentT left = term();
	
	if (currLex().isComparison()) {
		Lexem sign = currLex();
		nextLex();

		IdentT right = term();
		rpn.push_back(sign);

		left = checkTypes(left, sign, right);
	}	

	return left;
}

IdentT SyntacticAnalyzer::term() {
	IdentT left = term1();

	while (currLex().check(lex_plus) || currLex().check(lex_minus) || currLex().check(lex_or)) {
		Lexem sign = currLex();
		nextLex();

		IdentT right = term1();
		rpn.push_back(sign);
		left = checkTypes(left, sign, right);
	}

	return left;
}

IdentT SyntacticAnalyzer::term1() {
	IdentT left = entity();

	while (currLex().check(lex_mult) || currLex().check(lex_div) || currLex().check(lex_mod) || currLex().check(lex_and)) {
		Lexem sign = currLex();
		nextLex();

		IdentT right = entity();
		rpn.push_back(sign);
		left = checkTypes(left, sign, right);
	}

	return left;
}

IdentT SyntacticAnalyzer::entity() {
	if (currLex().check(LexemT::ident)) {
		rpn.push_back(currLex());

		return parseIdent();
	}

	if (currLex().isConst()) {
		rpn.push_back(currLex());

		Lexem currlex = currLex(); 
		nextLex();

		return currlex.getIdentT();
	}

	if (currLex().check(lex_not)) {
		nextLex();

		IdentT entT = entity();

		rpn.push_back(Lexem(LexemT::keyword, lex_not));

		if (entT != IdentT::type_bool)
			throw string("'not' can't invert non boolean expression in line ") + to_string(currLex().getLineNum()) + "\n" + getString();

		return entT;
	}
	
	if (currLex().check(lex_lparenthesis)) {
		nextLex();
		IdentT expT = parseExpression();

		if (!currLex().check(lex_rparanthesis))
			throw string("Uncapped bracket in line ") + to_string(currLex().getLineNum()) + "\n" + getString();
		nextLex();

		return expT;
	}

	// TODO: unary minus
	throw string("'") + currLex().getName() + "' is not an entity in line " + to_string(currLex().getLineNum()) + "\n" + getString();
}

void SyntacticAnalyzer::parseAsign(bool needSemicolon) {
	string name = currLex().getName();
	IdentT left = parseIdent();

	rpn.push_back(Lexem(LexemT::rpn_address, name));

	if (currLex().check(lex_asign)) {
		nextLex();
		IdentT right = parseExpression(); 

		if (!(left == right || (left == IdentT::type_real && right == IdentT::type_int)))
			throw string("'") + typeToString(right) + "' is incompatible with '" + typeToString(left) + "' in line " + to_string(currLex().getLineNum()) + "\n" + getString();

		rpn.push_back(Lexem(LexemT::delimeter, lex_asign));
	}
	else if (currLex().check(lex_inc) || currLex().check(lex_dec)) {
		if (left != IdentT::type_int)
			throw string("'") + currLex().getName() + "' is incompatible with '" + typeToString(left) + "' in line " + to_string(currLex().getLineNum()) + "\n" + getString();

		rpn.push_back(Lexem(currLex().check(lex_inc) ? LexemT::rpn_inc : LexemT::rpn_dec, currLex().getName()));

		nextLex();
	} 
	else {
		Lexem sign(LexemT::delimeter, "");

		if (currLex().check(lex_plus_value)) {
			sign.setName(lex_plus);
		}
		else if (currLex().check(lex_minus_value)) {
			sign.setName(lex_minus);
		}
		else if (currLex().check(lex_minus_value)) {
			sign.setName(lex_mult);
		}
		else if (currLex().check(lex_minus_value)) {
			sign.setName(lex_div);
		}
		else if (currLex().check(lex_minus_value)) {
			sign.setName(lex_mod);
		}
		else 
			throw string("Unknown operation '") + currLex().getName() + " in line " + to_string(currLex().getLineNum()) + "\n" + getString();

		nextLex();
		IdentT right = parseExpression();

		checkTypes(left, sign, right);

		rpn.push_back(Lexem(LexemT::rpn_short_op, sign.getName()));
	}

	if (needSemicolon) {
		if (!currLex().check(lex_semicolon)) 
			throw string("Missing ';' ")  + " in declaration";

		nextLex();
	}		
}


void SyntacticAnalyzer::printTable() const {
	cout << "Table:\n" << table;
}


string typeToString(IdentT type) {
	switch(type) {
		case IdentT::type_int: return str_type_int;
		case IdentT::type_real: return str_type_real;
		case IdentT::type_string: return str_type_string;
		case IdentT::type_bool: return str_type_bool;
		case IdentT::unknown: 
		default: return str_unknown;
	}
}

void SyntacticAnalyzer::printRPN() const{
	size_t index = 0;

	while (index < rpn.size()) {
		if (rpn[index].check(LexemT::rpn_fgo))
			cout << "[fgo] ";
		else if (rpn[index].check(LexemT::rpn_go))
			cout << "[go] ";
		else if (rpn[index].check(LexemT::rpn_address))
			cout << "[&" << rpn[index].getName() << "] ";
		else
			cout << "[" << rpn[index].getName() << "] ";
		
		index++;
	}
	cout << endl;
}