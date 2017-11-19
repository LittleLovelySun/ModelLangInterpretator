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