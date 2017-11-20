#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Enum.h"

class Lexem {
	LexemT type;
	std::string name;
public:
	Lexem(LexemT type, const std::string &name);
	Lexem(const Lexem &a);
	
	LexemT getType() const;
	std::string getName() const;
	friend std::ostream& operator<<(std::ostream &output, const Lexem &a);
};


std::ostream& operator<<(std::ostream &os, const Lexem &a);
