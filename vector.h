#ifndef _DESTRUCTIVE_VECTOR_H_
#define _DESTRUCTIVE_VECTOR_H_

#include "destructive_reasoning.h"
#include "symbol.h"

class Vector : public Symbol
{

	public:
		Vector(std::string n, std::string v);
		Vector(std::string n, double v[], int dimension);
		
	private:
		void setVector(std::string);

};

#endif
