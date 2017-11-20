#include "LexemAnalyzer.h"

using namespace std;

LexemAnalyzer::LexemAnalyzer(const string &in) {
	this->in = in;
}
LexemAnalyzer::LexemAnalyzer(ifstream &input) {
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

void LexemAnalyzer::analyze() {
	size_t ind = 0;

	while (ind < in.length()) {
		string s = string(1, in[ind]);
		if (isLetter(in[ind])) {
			//string s = string(s[ind], 1);
			ind++;

			while (ind < in.length() && (isLetter(in[ind]) || isDigit(in[ind]))) {
				s += in[ind];
				ind++;
			} 

			if (s == lex_false || s == lex_true) 
				lexems.push_back(Lexem(LexemT::const_bool, s));
			else if (s == lex_int) 
				lexems.push_back(Lexem(LexemT::data_int, s));
			else if (s == lex_real) 
				lexems.push_back(Lexem(LexemT::data_real, s));
			else if (s == lex_string) 
				lexems.push_back(Lexem(LexemT::data_string, s));
			else if (s == lex_bool)
				lexems.push_back(Lexem(LexemT::data_bool, s));

			else if (find(keywords.begin(), keywords.end(), s) < keywords.end()) 
				lexems.push_back(Lexem(LexemT::keyword, s));
			else {
				lexems.push_back(Lexem(LexemT::ident, s));
				table.addByName(s);
			}
		}
		else if (isDigit(in[ind])) {
			//string s = string(in[ind], 1);
			ind++;
			while (ind < in.length() && (isDigit(in[ind]) || string(in[ind], 1) == lex_comma)) {
				s += in[ind];
				ind++;
			}

			lexems.push_back(Lexem(s.find(lex_comma) == string::npos ? LexemT::const_int : LexemT::const_real, s));
		} 
		else if (string(1, in[ind]) == lex_quote) {
			//string s;
			ind++;
			while (ind < in.length() && string(in[ind], 1) != lex_quote) {
				s += in[ind];
				ind++;
			}

			lexems.push_back(Lexem(LexemT::const_string, s));
			ind++;
		}
		else if (string(in[ind], 1) == lex_comment) {
			while (ind < in.length() && in[ind] != '\n') 
				ind++;
			ind++;
		}
		else if (isLikeDelimeter(in[ind])) {
			string s1 = string(in[ind], 1);
			ind++;

			if (ind < in.length()) {
				string s2 = s1;
				s2 += in[ind];
				ind++;

				if (find(delimeters.begin(), delimeters.end(), s2) < delimeters.end()) {
					lexems.push_back(Lexem(LexemT::delimeter, s2));
					s = s2;
					ind++;
				}
				else if (find(delimeters.begin(), delimeters.end(), s1) < delimeters.end()) {
					lexems.push_back(Lexem(LexemT::delimeter, s1));
					s = s1;
				}
			}
			else if (find(delimeters.begin(), delimeters.end(), s1) < delimeters.end()) {
				lexems.push_back(Lexem(LexemT::delimeter, s1));
				s = s1;
			}
		}
		else if (in[ind] == ' ' || in[ind] == '\n' || in[ind] == '\t')
			ind++;
		else {
			lexems.push_back(Lexem(LexemT::unknown, string(in[ind], 1)));
			ind++;
		}
	//cout << "s: " << s << endl;
	}
}

void LexemAnalyzer::printLexems() {
	for (size_t i = 0; i < lexems.size(); i++) {
		lexems[i].print();
		cout << endl;
	}
}

vector<Lexem> &LexemAnalyzer::getLexems() {
	return lexems;
}