#include "Lexem.h"

Lexem::Lexem(LexemT type, const std::string &name, size_t num, size_t ind) {
	this->type = type;
	this->name = name;
	line_num = num;
	line_ind = ind;
}

Lexem::Lexem(const Lexem &a) {
	type = a.type;
	name = a.name;
	line_num = a.line_num;
	line_ind = a.line_ind;
}

LexemT Lexem::getType() const {
	return type;
}

std::string Lexem::getName() const{
	return name;
}

size_t Lexem::getLineNum() const {
	return line_num + 1;
}

size_t Lexem::getInd() const {
	return line_ind;
}

void Lexem::setName(const std::string &s) {
	name = s;
}

bool Lexem::check(const std::string &s) const {
	return name == s;
}

bool Lexem::check(LexemT t) const {
	return type == t;
}

bool Lexem::isData() const{
	return type == LexemT::data_int || type == LexemT::data_real || type == LexemT::data_string || type == LexemT::data_bool;
}

bool Lexem::isConst() const {
	return type == LexemT::const_int || type == LexemT::const_real || type == LexemT::const_string || type == LexemT::const_bool;
} 

IdentT Lexem::getIdentT() const{
	if (type == LexemT::data_int || type == LexemT::const_int)
		return IdentT::type_int;

	if (type == LexemT::data_real || type == LexemT::const_real)
		return IdentT::type_real;

	if (type == LexemT::data_string || type == LexemT::const_string) 
		return IdentT::type_string;

	if (type == LexemT::data_bool || type == LexemT::const_bool)
		return IdentT::type_bool;

	return IdentT::unknown;
}

bool Lexem::isAriphmetic() const {
	return name == lex_plus || name == lex_minus || name == lex_mult || name == lex_div || name == lex_mod;
}

bool Lexem::isComparison() const {
	return name == lex_equal || name == lex_nequal || name == lex_greater || name == lex_less || name == lex_greater_equal || name == lex_less_equal;
}

std::ostream& operator<<(std::ostream &output, const Lexem &a) {
	output << '|' << a.getName();
	std::string s = std::string(wid - 1 - a.getName().length(), ' ');
	output << s;

	switch (a.getType()) {
		case LexemT::unknown: std::cout << '|' << str_unknown << std::string(wid - 2 - str_unknown.length(), ' ') << '|';
		break;

		case LexemT::keyword: std::cout << '|'  << str_keyword << std::string(wid - 2 - str_keyword.length(), ' ') << '|';
		break;

		case LexemT::delimeter: std:: cout << '|'  << str_delimeter << std::string(wid - 2 - str_delimeter.length(), ' ') << '|';
		break;

		case LexemT::ident: std::cout << '|' <<  str_ident  << std::string(wid - 2 - str_ident.length(), ' ') << '|';
		break;

		case LexemT::const_int: std::cout << '|'  << str_const_int << std::string(wid - 2 - str_const_int.length(), ' ') << '|';
		break;

		case LexemT::const_real: std::cout << '|'  << str_const_real << std::string(wid - 2 - str_const_real.length(), ' ') << '|';
		break;

		case LexemT::const_string: std::cout << '|'  << str_const_string << std::string(wid - 2 - str_const_string.length(), ' ') << '|';
		break;

		case LexemT::const_bool: std::cout << '|'  << str_const_bool << std::string(wid - 2 - str_const_bool.length(), ' ') << '|';
		break;

		case LexemT::data_int: std::cout << '|'  << str_data_int << std::string(wid - 2 - str_data_int.length(), ' ') << '|';
		break;

		case LexemT::data_real: std::cout << '|'  << str_data_real << std::string(wid - 2 - str_data_real.length(), ' ') << '|';
		break;

		case LexemT::data_string: std::cout << '|'  << str_data_string << std::string(wid - 2 - str_data_string.length(), ' ') << '|';
		break;

		case LexemT::data_bool: std::cout << '|'  << str_data_bool << std::string(wid - 2 - str_data_bool.length(), ' ') << '|';
		break;
		default: ;
	}
	return output;
}
