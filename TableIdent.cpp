#include "TableIdent.h"

#include <vector>

/*TableIdent::TableIdent(const TableIdent &a) {
	for (size_t i = 0; i < a.size(); i++)
		tab.push_back(a.tab[i]);
}*/

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

std::ostream &operator<<(std::ostream &output, const TableIdent &a) {
	if (!a.tab.size()) 
		return output << "Table is empty" << std::endl;

	output << tmpIdent << tmpIdent << tmpIdent << tmpIdent << std::endl;
	output << '|' << str_type << std::string(widIdent - 1 - str_type.length(), ' ');
	output << '|' << str_name << std::string(widIdent - 1 - str_name.length(), ' ');
	output << '|' << str_value << std::string(widIdent - 1 - str_value.length(), ' ');
	output << '|' << str_declareted << std::string(widIdent - 2 - str_declareted.length(), ' ') << '|' << std::endl;
	output << tmpIdent << tmpIdent << tmpIdent << tmpIdent << std::endl;

	for (size_t i = 0; i < a.tab.size(); i++) 
		output << a.tab[i] << std::endl
	;
	output << tmpIdent << tmpIdent << tmpIdent << tmpIdent << std::endl;
	return output;
}

