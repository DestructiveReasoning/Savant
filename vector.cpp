#include "vector.h"
#include "Math.h"

Vector::Vector(std::string n, std::string v) :
	Symbol(n,Symbol::VectorType,false)
{
	setVector(v);
}

Vector::Vector(std::string n, double v[], int dim) :
	Symbol(n,Symbol::VectorType,false)
{
	vector = v;
	dimension = dim;
}

Vector * Vector::evaluateVectorMath(std::string equation) {
	if(!saneBrackets(equation)) return new Vector("_tmpBadVector",new double[0],0);
	std::stack<Symbol *> args;
	std::stack<std::string> ops;
	std::string current = std::string();

	for(int c = 0; c < equation.size(); c++) {
		if(equation[c] == ' ') {
			
		}
		else if	(equation[c] == '+' || equation[c] == '-' || equation[c] == '*' ||
			 equation[c] == '/' || equation[c] == '^') 
		{

		}
		else if(equation[c] == '(') {

		}
		else if(equation[c] == ')') {

		}
		else current += equation[c];
	}

	return new Vector("_tmpvec",new double[0],0);
}

void Vector::pushNewToken(std::string token, std::stack<Symbol *> args, std::stack<std::string> ops) {
	if(Txt::find(token,operators) != -1) {
		if(ops.size() == 0) {
			ops.push(token);
			return;
		} 
		if(Txt::find(token,operators) <= Txt::find(ops.top(),operators)) {
			if(token == "+") {
				Symbol *v = args.top();
				args.pop();
				Symbol *u = args.top();
				args.pop();
				if(u->getType() == Symbol::VectorType) {
					//TODO Vector addition
				}
				else {
					args.push(new Variable("_tmpvar",u->getValue()+v->getValue(),false));
				}
			}
			else if(token == "-") {
				Symbol *v = args.top();
				args.pop();
				Symbol *u = args.top();
				args.pop();
				if(u->getType() == Symbol::VectorType) {
					//TODO Vector subtraction
				}
				else {
					args.push(new Variable("_tmpvar",u->getValue()-v->getValue(),false));
				}
			}
			else if(token == "*") {
				Symbol *v = args.top();
				args.pop();
				Symbol *u = args.top();
				args.pop();
				if(u->getType() == Symbol::VectorType) {
					//TODO Vector scalar multiplication
				}
				else {
					args.push(new Variable("_tmpvar",u->getValue()*v->getValue(),false));
				}
			}
			else if(token == "/") {
				Symbol *v = args.top();
				args.pop();
				Symbol *u = args.top();
				args.pop();
				args.push(new Variable("_tmpvar",u->getValue()/v->getValue(),false));
			}
			else if(token == "^") {
				Symbol *v = args.top();
				args.pop();
				Symbol *u = args.top();
				args.pop();
				args.push(new Variable("_tmpvar", Math::exponential(u->getValue(),v->getValue(),false),false));
			}
			else if(token == "log") {
				Symbol *v = args.top();
				args.pop();
				args.push(new Variable("_tmpvar",log(v->getValue())/log(10),false));
			}
			else if(token == "ln") {
				Symbol *v = args.top();
				args.pop();
				args.push(new Variable("_tmpvar",log(v->getValue()),false));
			}
			else if(token == "sin") {
				Symbol *v = args.top();
				args.pop();
				args.push(new Variable("_tmpvar",sin(v->getValue()),false));
			}
			else if(token == "cos") {
				Symbol *v = args.top();
				args.pop();
				args.push(new Variable("_tmpvar",cos(v->getValue()),false));
			}
			else if(token == "tan") {
				Symbol *v = args.top();
				args.pop();
				args.push(new Variable("_tmpvar",tan(v->getValue()),false));
			}
		}
	}
	else {
		Symbol *newArg;
		if(token[0] == '<') {
			newArg = new Vector("_tmpvec",token);
			args.push(newArg);
		}
		else {
			newArg = new Variable	("_tmpvar"
						,Math::evaluateRPN(Math::infixToRPN(token),0,false),false);
			args.push(newArg);
		}
	}
}

void Vector::setVector(std::string v) {
	std::string *nums;
	int size = 0;
	for(int c = 0; c < v.size(); c++) {
		if(v[c] == ',') size++;
	}
	size++;
	nums = new std::string[size]();
	int numIndex = 0;
	for(int c = 0; v[c] != '>'; c++) {
		std::string nextNum;
		if(v[c] == '<') continue;
		if(v[c] == ',') numIndex++;
		else nums[numIndex] += v[c];
	}

	vector = new double[size]();
	for(int c = 0; c < size; c++) {
		vector[c] = Math::evaluateRPN(Math::infixToRPN(nums[c]),0,false);
	}
	dimension = size;
}

std::string Vector::toString() {
	std::stringstream vec = std::stringstream();
	vec << "<";
	for(int c = 0; c < dimension; c++) {
		vec << vector[c];
		if(c != dimension - 1) vec << ", ";
	}
	vec << ">";

	return vec.str();
}

bool Vector::saneBrackets(std::string s) {
	std::vector<char> brackets;
	for(int c = 0; c < s.size(); c++) {
		if(s[c] == '<') brackets.push_back('<');
		if(s[c] == '>') {
			if(brackets.size() == 0) return false;
			brackets.pop_back();
		}
	}
	return brackets.size() == 0;
}
//std::string Vector::operators[] = 	{"+","-","*","/","^","log","ln","sin","cos"
//					,"tan","asin","acos","atan","dot","cross","sqrt"};
std::vector<std::string> Vector::initOperators() {
	std::vector<std::string> operators;
	operators.push_back("+");
	operators.push_back("-");
	operators.push_back("*");
	operators.push_back("/");
	operators.push_back("^");
	operators.push_back("log");
	operators.push_back("ln");
	operators.push_back("sin");
	operators.push_back("cos");
	operators.push_back("tan");
	operators.push_back("asin");
	operators.push_back("acos");
	operators.push_back("atan");
	operators.push_back("dot");
	operators.push_back("cross");
	operators.push_back("sqrt");
}
std::vector<std::string> Vector::operators = initOperators();
