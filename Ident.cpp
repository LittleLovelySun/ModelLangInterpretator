#include "Ident.h"

Ident::Ident(const std::string &name, const std::string &value, IdentT type, bool dec) {
	this->name = name;
	this->value = value;
	this->type = type;
	declared = dec;
}

Ident::Ident(const Ident &a) {
	name = a.getName();
	value = a.getValue();
	type = a.getType();
	declared = a.getDec();
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

std::ostream& operator<<(std::ostream &output, const Ident &a) {
	output << '|';

	switch(a.getType()) {
		case IdentT::unknown: std::cout << str_unknown << std::string(widIdent - 1 - str_unknown.length(), ' ') << '|';
		break;

		case IdentT::type_int: std::cout << str_type_int << std::string(widIdent - 1 - str_type_int.length(), ' ') << '|';
		break;
		
		case IdentT::type_real: std::cout << str_type_real << std::string(widIdent - 1 - str_type_real.length(), ' ') << '|';
		break;
		
		case IdentT::type_string: std::cout << str_type_string << std::string(widIdent - 1 - str_type_string.length(), ' ') << '|';
		break;
		
		case IdentT::type_bool: std::cout << str_type_bool << std::string(widIdent - 1 - str_type_bool.length(), ' ') << '|';
		break;
	}

	output << a.getName() << std::string(widIdent - 1 - a.getName().length(), ' ') << '|';
	output << a.getValue() << std::string(widIdent - 1 - a.getValue().length(), ' ') << '|';
	output << a.getDec() << std::string(widIdent - 2 - 1, ' ') << '|';

	return output;
}
