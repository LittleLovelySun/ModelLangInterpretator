#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Enum.h"

class Lexem {
	LexemT type;
	std::string name;
	size_t line_num;
	size_t line_ind;
public:
	Lexem(LexemT type, const std::string &name, size_t num = 0, size_t ind = 0);
	Lexem(const Lexem &a);
	
	bool check(const std::string &s) const;
	bool check(LexemT t) const;

	bool isData() const;
	bool isConst() const;

	LexemT getType() const;
	IdentT getIdentT() const;
	size_t getLineNum() const;
	size_t getInd() const;

	bool isAriphmetic() const;
	bool isComparison() const;
	
	void setName(const std::string &s);
	std::string getName() const;

	friend std::ostream& operator<<(std::ostream &output, const Lexem &a);
};

std::ostream& operator<<(std::ostream &os, const Lexem &a);