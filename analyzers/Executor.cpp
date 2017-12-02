#include "Executor.h"

using namespace std;

Executor::Executor(const vector<Lexem> &rpn, const TableIdent &table) {
	this->rpn = rpn;
	this->table = table;
 	ind = 0;
}

double Executor::LtoD(Lexem &lex) {
	return stod(lex.getName());
}

double Executor::LtoD(Ident *ident) {
	return stod(ident->getValue());
}

void Executor::executeAriphmetic() {
	Lexem second = stack.top();
	stack.pop();

	Lexem first = stack.top();
	stack.pop();

	if (rpn[ind].check(lex_plus)) {
		if (first.check(LexemT::const_string)) 
			stack.push(Lexem(LexemT::const_string, first.getName() + second.getName()));
		else if (first.check(LexemT::const_int) && second.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_int, to_string(stoi(first.getName()) + stoi(second.getName()))));
		else 
			stack.push(Lexem(LexemT::const_real, to_string(LtoD(first) + LtoD(second))));
	}

	else if (rpn[ind].check(lex_minus)) {
		if (first.check(LexemT::const_int) && second.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_int, to_string(stoi(first.getName()) - stoi(second.getName()))));
		else 
			stack.push(Lexem(LexemT::const_real, to_string(LtoD(first) - LtoD(second))));
	}

	else if (rpn[ind].check(lex_mult)) {
		if (first.check(LexemT::const_int) && second.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_int, to_string(stoi(first.getName()) * stoi(second.getName()))));
		else 
			stack.push(Lexem(LexemT::const_real, to_string(LtoD(first) * LtoD(second))));
	}

	else if (rpn[ind].check(lex_div)) {
		if (second.getName() == "0") 
			throw string("Division by zero!");

		if (first.check(LexemT::const_int) && second.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_int, to_string(stoi(first.getName()) / stoi(second.getName()))));
		else 
			stack.push(Lexem(LexemT::const_real, to_string(LtoD(first) / LtoD(second))));
	}
	else {
		if (second.getName() == "0") 
			throw string("Division by zero!");
		stack.push(Lexem(LexemT::const_int, to_string(stoi(first.getName()) % stoi(second.getName()))));
	}	
}

void Executor::executeShortOp() {
	Lexem second = stack.top();
	stack.pop();


	Ident* ident = table.getByName(stack.top().getName());
	stack.pop();

	if (rpn[ind].check(lex_plus_value)) {
		if (ident->getType() == IdentT::type_string) 
			ident->setValue(ident->getValue() + second.getName());
		else if (ident->getType() == IdentT::type_int && second.check(LexemT::const_int)) 
			ident->setValue(to_string(stoi(ident->getValue()) + stoi(second.getName())));
		else 
			ident->setValue(to_string(LtoD(ident) + LtoD(second)));
	}

	else if (rpn[ind].check(lex_minus_value)) {
		if (ident->getType() == IdentT::type_int && second.check(LexemT::const_int)) 
			ident->setValue(to_string(stoi(ident->getValue()) - stoi(second.getName())));
		else 
			ident->setValue(to_string(LtoD(ident) - LtoD(second)));
	}

	else if (rpn[ind].check(lex_mult_value)) {
		if (ident->getType() == IdentT::type_int && second.check(LexemT::const_int))
			ident->setValue(to_string(stoi(ident->getValue()) * stoi(second.getName())));
		else 
			ident->setValue(to_string(LtoD(ident) * LtoD(second)));
	}

	else if (rpn[ind].check(lex_div_value)) {
		if (second.getName() == "0") 
			throw string("Division by zero!");

		if (ident->getType() == IdentT::type_int && second.check(LexemT::const_int))
			ident->setValue(to_string(stoi(ident->getValue()) / stoi(second.getName())));
		else 
			ident->setValue(to_string(LtoD(ident) / LtoD(second)));
	}
	else {
		if (second.getName() == "0") 
			throw string("Division by zero!");
		ident->setValue(to_string(stoi(ident->getValue()) % stoi(second.getName())));
	}	
}

void Executor::executeComparison() {
	Lexem second = stack.top();
	stack.pop();

	Lexem first = stack.top();
	stack.pop();

	if (rpn[ind].check(lex_equal)) {
		if (second.check(LexemT::const_real) || first.check(LexemT::const_real)) 
			stack.push(Lexem(LexemT::const_bool, LtoD(second) == LtoD(first) ? lex_true : lex_false));
		
		else
			stack.push(Lexem(LexemT::const_bool, second.getName() == first.getName() ? lex_true : lex_false));
	}
	else if (rpn[ind].check(lex_nequal)) {
		if (second.check(LexemT::const_real) || first.check(LexemT::const_real)) 
			stack.push(Lexem(LexemT::const_bool, LtoD(second) != LtoD(first) ? lex_true : lex_false));
		
		else
			stack.push(Lexem(LexemT::const_bool, second.getName() != first.getName() ? lex_true : lex_false));
	}
	else if (rpn[ind].check(lex_greater)) {
		if (second.check(LexemT::const_real) || first.check(LexemT::const_real) || first.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_bool, LtoD(second) < LtoD(first) ? lex_true : lex_false));

		else if (second.check(LexemT::const_bool)) 
			stack.push(Lexem(LexemT::const_bool, (second.getName() == lex_false && first.getName() == lex_true) ? lex_true : lex_false));

		else
			stack.push(Lexem(LexemT::const_bool, second.getName() < first.getName() ? lex_true : lex_false));
	}
	else if (rpn[ind].check(lex_less)) {
		if (second.check(LexemT::const_real) || first.check(LexemT::const_real) || first.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_bool, LtoD(second) > LtoD(first) ? lex_true : lex_false));

		else if (second.check(LexemT::const_bool)) 
			stack.push(Lexem(LexemT::const_bool, (second.getName() == lex_true && first.getName() == lex_false) ? lex_true : lex_false));

		else
			stack.push(Lexem(LexemT::const_bool, second.getName() > first.getName() ? lex_true : lex_false));
	}
	else if (rpn[ind].check(lex_greater_equal)) {
		if (second.check(LexemT::const_real) || first.check(LexemT::const_real) || first.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_bool, LtoD(second) <= LtoD(first) ? lex_true : lex_false));

		else if (second.check(LexemT::const_bool)) 
			stack.push(Lexem(LexemT::const_bool, (second.getName() == lex_true && first.getName() == lex_false) ? lex_false : lex_true));

		else
			stack.push(Lexem(LexemT::const_bool, second.getName() <= first.getName() ? lex_true : lex_false));
	}
	else if (rpn[ind].check(lex_less_equal)) {
		if (second.check(LexemT::const_real) || first.check(LexemT::const_real) || first.check(LexemT::const_int)) 
			stack.push(Lexem(LexemT::const_bool, LtoD(second) >= LtoD(first) ? lex_true : lex_false));

		else if (second.check(LexemT::const_bool)) 
			stack.push(Lexem(LexemT::const_bool, (second.getName() == lex_false && first.getName() == lex_true) ? lex_false : lex_true));

		else
			stack.push(Lexem(LexemT::const_bool, second.getName() >= first.getName() ? lex_true : lex_false));
	}
}

void Executor::executeKeyword() {
	if (rpn[ind].check(lex_write) || rpn[ind].check(lex_writeln)) {
		cout << stack.top().getName();

		if (rpn[ind].check(lex_writeln))
			cout << endl;
		stack.pop();
	}
	else if (rpn[ind].check(lex_read)) {
		string value;
		Ident *ident = table.getByName(stack.top().getName());

		if (ident->getType() == IdentT::type_int) {
			int res;
			cin >> res;
			value = to_string(res);
		}
		else if (ident->getType() == IdentT::type_real) {
			double res;
			cin >> res;
			value = to_string(res);
		}
		else if (ident->getType() == IdentT::type_bool) {
			cin >> value;

			if (value != lex_false && value != lex_true)
				throw string("'") + value + "' is not boolean";	
		}

		else if (ident->getType() == IdentT::type_string) 
			cin >> value;
		
		ident->setValue(value);
		stack.pop();
	}
	else if (rpn[ind].check(lex_not)) {
		stack.top().setName(stack.top().check(lex_false) ? lex_true : lex_false);
	}
	else {
		bool second = stack.top().check(lex_true);
		stack.pop();

		bool first = stack.top().check(lex_true);
		stack.pop();

		if (rpn[ind].check(lex_or)) 
			stack.push(Lexem(LexemT::const_bool, (second || first) ? lex_true : lex_false));
		else
			stack.push(Lexem(LexemT::const_bool, (second && first) ? lex_true : lex_false));	
	}
}

void Executor::execute() {
	try {
		while (ind < rpn.size()) {
			if (rpn[ind].isConst() || rpn[ind].check(LexemT::rpn_address) || rpn[ind].check(LexemT::rpn_label)) {
				stack.push(rpn[ind]);
			}
			else if (rpn[ind].check(LexemT::ident)) {
				stack.push(table.getByName(rpn[ind].getName())->toLexem());
			}			
			else if (rpn[ind].check(LexemT::keyword)) {
				executeKeyword();
			}
			else if (rpn[ind].check(lex_asign)) {
				string value = stack.top().getName();
				stack.pop();

				table.getByName(stack.top().getName())->setValue(value);
				stack.pop();
			}
			else if (rpn[ind].check(LexemT::rpn_go)) {
				ind = stoi(stack.top().getName()) - 1;
				stack.pop();
			}
			else if (rpn[ind].isAriphmetic()) {
				executeAriphmetic();
			}
			else if (rpn[ind].check(LexemT::rpn_short_op)) {
				executeShortOp();
			}
			else if (rpn[ind].isComparison()){
				executeComparison();
			}
			else if (rpn[ind].check(LexemT::rpn_inc)) {
				Ident *ident = table.getByName(stack.top().getName());
				ident->setValue(to_string(stoi(ident->getValue()) + 1));
				stack.pop();
			}
			else if (rpn[ind].check(LexemT::rpn_dec)) {
				Ident *ident = table.getByName(stack.top().getName());
				ident->setValue(to_string(stoi(ident->getValue()) - 1));
				stack.pop();
			}
			else if (rpn[ind].check(LexemT::rpn_fgo)) {
				size_t label = stoi(stack.top().getName());
				stack.pop();

				if (stack.top().getName() == lex_false) 
					ind = label - 1;

				stack.pop();
			}

			ind++;
		}
	} catch (string msg) {
		cout << "Execution error: " << msg << endl;
	}
}