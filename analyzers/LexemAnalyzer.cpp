#include "LexemAnalyzer.h"

using namespace std;

LexemAnalyzer::LexemAnalyzer(const string &in) {
	this->in = in;
}
LexemAnalyzer::LexemAnalyzer(ifstream &input) {
	if (!input.good())
		throw string("File was not open.");

	in = string(istreambuf_iterator<char>(input), istreambuf_iterator<char>());
}

bool LexemAnalyzer::isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool LexemAnalyzer::isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool LexemAnalyzer::isLikeDelimeter(char c) {
	for (size_t i = 0; i < delimeters.size(); i++)
		if (c == delimeters[i][0])
			return true;
	return false;
}

bool LexemAnalyzer::analyze() {
	size_t ind = 0;
	size_t line_num = 0;
	size_t line_ind = 0;

	while (ind < in.length()) {
		if (isLetter(in[ind])) {

			string s = string(1, in[ind]);
			ind++;

			while (ind < in.length() && (isLetter(in[ind]) || isDigit(in[ind]))) {
				s += in[ind];
				ind++;
			} 

			if (s == lex_false || s == lex_true) 
				lexems.push_back(Lexem(LexemT::const_bool, s, line_num, line_ind));
			else if (s == lex_int) 
				lexems.push_back(Lexem(LexemT::data_int, s, line_num, line_ind));
			else if (s == lex_real) 
				lexems.push_back(Lexem(LexemT::data_real, s, line_num, line_ind));
			else if (s == lex_string) 
				lexems.push_back(Lexem(LexemT::data_string, s, line_num, line_ind));
			else if (s == lex_bool)
				lexems.push_back(Lexem(LexemT::data_bool, s, line_num, line_ind));

			else if (find(keywords.begin(), keywords.end(), s) < keywords.end()) 
				lexems.push_back(Lexem(LexemT::keyword, s, line_num, line_ind));
			else {
				lexems.push_back(Lexem(LexemT::ident, s, line_num, line_ind));
				table.addByName(s);
			}
		}
		else if (isDigit(in[ind])) {
			string s = string(1, in[ind]);
			ind++;
			int point = 0;
			while (ind < in.length() && (isDigit(in[ind]) || string(1, in[ind]) == lex_point)) {
				if ((point += (string(1, in[ind]) == lex_point)) > 1) {
					cout << "Real constant must contain only one point!" << endl;
					return false;					
				}

				s += in[ind];
				ind++;
			}

			lexems.push_back(Lexem(s.find(lex_point) == string::npos ? LexemT::const_int : LexemT::const_real, s, line_num, line_ind));
		} 
		else if (string(1, in[ind]) == lex_quote) { 
			string s;
			ind++;
			while (ind < in.length() && string(1, in[ind]) != lex_quote) {
				s += in[ind];
				ind++;
			}

			lexems.push_back(Lexem(LexemT::const_string, s, line_num, line_ind));
			ind++;
		}
		else if (string(1, in[ind]) == lex_comment) {
			while (ind < in.length() && in[ind] != '\n') 
				ind++;
			ind++;
		}
		else if (isLikeDelimeter(in[ind])) {
			string s1 = string(1, in[ind]);
			ind++;

			if (ind < in.length()) {
				string s2 = s1;
				s2 += in[ind];

				if (find(delimeters.begin(), delimeters.end(), s2) < delimeters.end()) {
					lexems.push_back(Lexem(LexemT::delimeter, s2, line_num, line_ind));
					ind++;
				}
				else if (find(delimeters.begin(), delimeters.end(), s1) < delimeters.end()) 
					lexems.push_back(Lexem(LexemT::delimeter, s1, line_num, line_ind));
			}
			else if (find(delimeters.begin(), delimeters.end(), s1) < delimeters.end()) 
				lexems.push_back(Lexem(LexemT::delimeter, s1, line_num, line_ind));
			
		}
		else if (in[ind] == ' ' || in[ind] == '\n' || in[ind] == '\t')  {
			if (in[ind] == '\n') {
				line_num++;
				line_ind = ind + 1;
			}
			ind++;
		}
		else {
			cout << "Unknown lexem '" << in[ind] << endl;
			return false;
		}
	}
	return true;
}

void LexemAnalyzer::printLexems() const {
	if (!lexems.size())
		return ;

	cout << tmp << tmp << endl;
	cout << '|' << str_type << string(wid - 1 - str_type.length(), ' ');
	cout << '|' << str_name << string(wid - 2 - str_name.length(), ' ');
	cout << '|' << endl << tmp << tmp << endl;
	for (size_t i = 0; i < lexems.size(); i++)
		cout << lexems[i] << endl;
	
	cout << tmp << tmp << endl;
}



void LexemAnalyzer::printTable() const {
	cout << "Table:\n" << table;
}

string &LexemAnalyzer::getString() {
	return in;
}

vector<Lexem> &LexemAnalyzer::getLexems() {
	return lexems;
}

TableIdent &LexemAnalyzer::getTable() {
	return table;
}