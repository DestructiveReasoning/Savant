#ifndef _DESTRUCTIVE_VECTOR_H_
#define _DESTRUCTIVE_VECTOR_H_

#include "destructive_reasoning.h"
#include "symbol.h"
#include <sstream>

class Vector : public Symbol
{

	public:
		Vector(std::string n, std::string v);
		Vector(std::string n, double v[], int dimension);

		virtual std::string toString();

		static bool saneBrackets(std::string s);
		static Vector *evaluateVectorMath(std::string);
		
	private:
		void setVector(std::string);

};

#endif
