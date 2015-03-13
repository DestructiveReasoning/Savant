#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "destructive_reasoning.h"

class Variable
{
	public:
		Variable(std::string n, double v) : name(n), value(v) {};
		std::string getName();
		double getValue(); 

		void setValue(double val);

	private:
		std::string name;
		double value;
};

#endif
