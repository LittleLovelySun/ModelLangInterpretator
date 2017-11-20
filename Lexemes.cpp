#include "Lexemes.h"

Lexem::Lexem(LexemT type, const std::string &name) {
	this->type = type;
	this->name = name;
}

LexemT Lexem::getType() const {
	return type;
}

std::string Lexem::getName() const{
	return name;
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
	}
	return output;
}

Ident::Ident(const std::string &name, const std::string &value, IdentT type, bool dec) {
	this->name = name;
	this->value = value;
	this->type = type;
	declared = dec;
}

void Ident::setValue(const std::string &value) {
	this->value = value;
}

void Ident::setDec(bool dec) {
	declared = dec;
}

void Ident::setType(IdentT type) {
	this->type = type;
}

std::string Ident::getName() const{
	return name;
}

std::string Ident::getValue() const{
	return value;
}

IdentT Ident::getType() const{
	return type;
}

bool Ident::getDec() const{
	return declared;
}

void TableIdent::addByName(const std::string &name) {
	for (size_t i = 0; i < tab.size(); i++) 
		if (tab[i].getName() == name) 
			return;

	tab.push_back(name);
}

Ident* TableIdent::getByName(const std::string &name) {
	for (size_t i = 0; i < tab.size(); i++) 
		if (tab[i].getName() == name) 
			return &tab[i];

	return nullptr;
}