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

