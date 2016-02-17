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
	return new Vector("_tmpvec",new double[0],0);
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
