#include "symbol.h"
#include "Math.h"
#include "vector.h"

Vector *Symbol::addVectors(Symbol u, Symbol v) {
	if(u.getType() != Symbol::VectorType || v.getType() != Symbol::VectorType) {
		printf("Can't do vector addition: %s and %s must both be vectors\n",u.getName(),v.getName());
		return nullptr;
	}
	if(u.getVectorDimension() != v.getVectorDimension()) {
		printf("Can't do vector addition: %s and %s must have the same dimension\n",u.getName(),v.getName());
		return nullptr;
	}

	double *components = new double[u.getVectorDimension()]();
	for(int c = 0; c < u.getVectorDimension(); c++) {
		components[c] = u.getVectorComponents()[c] + v.getVectorComponents()[c];
	}
	return new Vector("UNNAMED_VECTOR",components,u.getVectorDimension());
}

Vector *Symbol::subVectors(Symbol u, Symbol v) {
	if(u.getType() != Symbol::VectorType || v.getType() != Symbol::VectorType) {
		printf("Can't do vector subtraction: %s and %s must both be vectors\n",u.getName(),v.getName());
		return nullptr;
	}
	if(u.getVectorDimension() != v.getVectorDimension()) {
		printf("Can't do vector addition: %s and %s must have the same dimension\n",u.getName(),v.getName());
		return nullptr;
	}

	double *components = new double[u.getVectorDimension()]();
	for(int c = 0; c < u.getVectorDimension(); c++) {
		components[c] = u.getVectorComponents()[c] - v.getVectorComponents()[c];
	}
	return new Vector("UNNAMED_VECTOR",components,u.getVectorDimension());
}

Vector *Symbol::mulVectors(double k, Symbol u) {
	if(u.getType() != Symbol::VectorType) {
		printf("Can't do vector-scalar multiplication: %s is not a vector\n",u.getName());
		return nullptr;
	}
	double *components = new double[u.getVectorDimension()]();
	for(int c = 0; c < u.getVectorDimension(); c++) {
		components[c] = k * u.getVectorComponents()[c];
	}
	return new Vector("UNNAMED_VECTOR",components,u.getVectorDimension());
}

Vector *Symbol::normalizeVector(Symbol u) {
	if(u.getType() != Symbol::VectorType) {
		printf("Can't normalize %s: it isn't a vector...\n", u.getName());
		return nullptr;
	}
	double length = 0;
	double *components = u.getVectorComponents();
	for(int c = 0; c < u.getVectorDimension(); c++) {
		length += components[c] * components[c];
	}
	length = sqrt(length);
	return mulVectors(1/length,u);
}

double Symbol::dot(Symbol u, Symbol v) {
	if(u.getType() != Symbol::VectorType || v.getType() != Symbol::VectorType) {
		printf("Can't do dot product: %s and %s must be vectors\n",u.getName(),v.getName());
		return 0.0;
	}
	if(u.getVectorDimension() != v.getVectorDimension()) {
		printf("Can't do dot product: %s and %s must be of the same dimension\n",u.getName(),v.getName());
		return 0.0;
	}
	double product = 0.0;
	for(int c = 0; c < u.getVectorDimension(); c++) {
		product += u.getVectorComponents()[c] * v.getVectorComponents()[c];
	}
	return product;
}

Vector *Symbol::cross(Symbol u, Symbol v) {
/*
 * |i j k|
 * |a b c| u
 * |d e f| v
 */

	if(u.getType() != Symbol::VectorType || v.getType() != Symbol::VectorType) {
		printf("Can't compute cross product: %s and %s must be 3 dimensional vectors\n",u.getName(),v.getName());
		return nullptr;
	}

	if(u.getVectorDimension() != 3 || v.getVectorDimension() != 3) {
		printf("Can't compute cross product: Vectors must both be 3 dimensional\n");
	}

	double *uComponents = u.getVectorComponents();
	double *vComponents = v.getVectorComponents();
	double res[3];
	res[0] = uComponents[1] * vComponents[2] - uComponents[2] * vComponents[1];
	res[1] = -1 * (uComponents[0] * vComponents[2] - uComponents[2] - vComponents[0]);
	res[2] = uComponents[0] * vComponents[1] - uComponents[1] * vComponents[0];
	return new Vector("UNNAMED_VECTOR",res,3);
}
