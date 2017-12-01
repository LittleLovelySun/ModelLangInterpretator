#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Enum.h"

class Ident {
	IdentT type;
	std::string name;
	std::string value; 
	bool declared;
public:
	Ident(const std::string &name, const std::string &value = "", IdentT type = IdentT::unknown, bool dec = false);
	Ident(const Ident &a);

	void setValue(const std::string &value);
	void setDec(bool dec);
	void setType(IdentT type);
	void setAsDefault();

	IdentT getType() const;
	std::string getName() const;
	std::string getValue() const;
	bool getDec() const;

	std::string TypeToString() const;

	friend std::ostream& operator<<(std::ostream &output, const Ident &a);
};

std::ostream& operator<<(std::ostream &os, const Ident &a);
