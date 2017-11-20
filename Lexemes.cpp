#include "Lexemes.h"

Lexem::Lexem(LexemT type, const std::string &name) {
	this->type = type;
	this->name = name;
}

LexemT Lexem::getType() {
	return type;
}

std::string Lexem::getName() {
	return name;
}

void Lexem::print() {
	std::cout << "type: ";
	switch (type) {
		case LexemT::unknown: std::cout << "unknown";
		break;

		case LexemT::keyword: std::cout << "keyword";
		break;

		case LexemT::delimeter: std:: cout << "delimeter";
		break;

		case LexemT::ident: std::cout << "delimeter";
		break;

		case LexemT::const_int: std::cout << "const_int";
		break;

		case LexemT::const_real: std::cout << "const_real";
		break;

		case LexemT::const_string: std::cout << "const_string";
		break;

		case LexemT::const_bool: std::cout << "const_bool";
		break;

		case LexemT::data_int: std::cout << "data_int";
		break;

		case LexemT::data_real: std::cout << "data_real";
		break;

		case LexemT::data_string: std::cout << "data_string";
		break;

		case LexemT::data_bool: std::cout << "data_bool";
		break;
	}

	std::cout << "\t name: " << name;
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

std::string Ident::getName() {
	return name;
}

std::string Ident::getValue() {
	return value;
}

IdentT Ident::getType() {
	return type;
}

bool Ident::getDec() {
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