#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "destructive_reasoning.h"

class Vector;

class Symbol
{
	public:
		enum Type {VariableType,MatrixType,VectorType};
		Symbol(std::string n, Type t, bool isConstant) : name(n), type(t), constant(isConstant) {};
		inline std::string getName() { return name; };
		inline Type getType() { return type; };
		inline int getVectorDimension() { return dimension; };
		inline double *getVectorComponents() { return vector; };
		inline bool isConstant() { return constant; };
		virtual double getValue() { return 0; };
		virtual void setValue(double v) { value = v; };
		virtual std::string toString() {};

		static Vector *addVectors(Symbol,Symbol);
		static Vector *subVectors(Symbol,Symbol);
		static Vector *mulVectors(double k, Symbol);
		static Vector *normalizeVector(Symbol);
		static double dot(Symbol,Symbol);
		static Vector *cross(Symbol,Symbol);

	protected:
		std::string name;
		Type type;
		bool constant;
		double value;

		double *vector;
		int dimension;

		double **matrix;
		double rows;
		double columns;
};

#endif
