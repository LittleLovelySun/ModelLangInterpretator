#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Enum.h"
#include "Ident.h"

class TableIdent {
	std::vector<Ident> tab;
public:
	//TableIdent(const TableIdent &a);

	void addByName(const std::string &name);
	Ident* getByName(const std::string &name);
	friend std::ostream &operator<<(std::ostream &output, const TableIdent &a);
};

std::ostream &operator<<(std::ostream &os, const TableIdent &a);
