#pragma once

#include <iostream>
#include <string>
#include <vector>

// Begin 
const std::string lex_program = "program";

// Datatypes
const std::string lex_int = "int";
const std::string lex_real = "real";
const std::string lex_string = "string";
const std::string lex_bool = "bool";

// Constants
const std::string lex_true = "true";
const std::string lex_false = "false";

// Loops
const std::string lex_while = "while";
const std::string lex_do = "do";
const std::string lex_for = "for";
const std::string lex_break = "break";

// Conditional
const std::string lex_if = "if";
const std::string lex_else = "else";

// IO functions
const std::string lex_read = "read";
const std::string lex_write = "write";

// Boolean operations
const std::string lex_not = "not";
const std::string lex_and = "and";
const std::string lex_or = "or";

// DELIMETERS
const std::string lex_comma = ",";
const std::string lex_semicolon = ";";

const std::string lex_lbrace = "{";
const std::string lex_rbrace = "}";

const std::string lex_lparenthesis = "(";
const std::string lex_rparanthesis = ")";

// Ariphmetics
const std::string lex_plus = "+";
const std::string lex_minus = "-";
const std::string lex_mult = "*";
const std::string lex_div = "/";
const std::string lex_mod = "%";

const std::string lex_plus_value = "+=";
const std::string lex_minus_value = "-=";
const std::string lex_mult_value = "*=";
const std::string lex_div_value = "/=";
const std::string lex_mod_value = "%=";

const std::string lex_inc = "++";
const std::string lex_dec = "--";

// Comparison
const std::string lex_asign = "=";
const std::string lex_equal = "==";
const std::string lex_nequal = "!=";
const std::string lex_greater = ">";
const std::string lex_less = "<";
const std::string lex_greater_equal = ">=";
const std::string lex_less_equal = "<=";

// Comment
const std::string lex_comment = "#";
const std::string lex_quote = "\"";

// Types of lexemes
enum class LexemT {
	unknown = -1, //+
	keyword, //+
	delimeter, //+
	ident, //+
	const_int, //+
	const_real, //+
	const_string, //+
	const_bool, //+
	data_int, //+
	data_real, //+
	data_string, //+
	data_bool  //+
};

enum class IdentT {
	unknown = -1,
	type_int,
	type_real,
	type_string,
	type_bool,
};

const std::vector<std::string> keywords = {
	lex_program,
	lex_while, lex_do, lex_for, lex_break,
	lex_if, lex_else,
	lex_read, lex_write,
	lex_not, lex_and, lex_or
};

const std::vector<std::string> delimeters = {
	lex_comma, lex_semicolon, 
	lex_lbrace, lex_rbrace, lex_lparenthesis, lex_rparanthesis,

	lex_plus, lex_minus, lex_mult, lex_div, lex_mod,
	lex_plus_value, lex_minus_value, lex_mult_value, lex_div_value, lex_mod_value,

	lex_inc, lex_dec,

	lex_asign, lex_equal, lex_nequal, lex_greater, lex_less, lex_greater_equal, lex_less_equal,

	lex_comment, lex_quote
};

class Lexem {
	LexemT type;
	std::string name;
public:
	Lexem(LexemT type, const std::string &name);
	LexemT getType();
	std::string getName();
	void print();
};

class Ident {
	IdentT type;
	std::string name;
	std::string value; 
	bool declared;
public:
	Ident(const std::string &name, const std::string &value = "", IdentT type = IdentT::unknown, bool dec = false);
	void setValue(const std::string &value);
	void setDec(bool dec);
	void setType(IdentT type);

	IdentT getType();
	std::string getName();
	std::string getValue();
	bool getDec();
};

class TableIdent {
	std::vector<Ident> tab;
public:
	void addByName(const std::string &name);
	Ident* getByName(const std::string &name);
};