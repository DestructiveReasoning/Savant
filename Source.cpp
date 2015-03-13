#include "destructive_reasoning.h"
#include "variable.h"
#include "Math.h"
#include "Txt.h"
#include <iostream>
#include <limits>
#include <cstdio>

#define TITLE "Savant"

std::string substring(std::string, int, int);

void solveQuadratic();

int main(int argc, char *argv[])
{
	bool running = true;
	std::string infix;
	std::vector<Variable *> variables;
	
	printf("\n%s\nv0.1.0\nCopyright (C) 2015 Harley Wiltzer\nPowered by Har Wiltz's Destructive Reasoning\n", TITLE);
	printf("This free software includes exactly 0 warranties\n\n");

	variables.push_back(new Variable("ans",0.0));
	variables.push_back(new Variable("pi",M_PI));
	variables.push_back(new Variable("e",M_E));

	int vn;

	while(running)
	{
		Math::setVariables(variables);
		printf("savant> ");
		std::getline(std::cin,infix);
		if(infix == "quit" || infix == "exit") running = false;
		else if(infix == "clear") system("clear");
		else if(infix == "quadratic")
		{
			Math::variables = variables;
			printf("~$ Starting Quadratic Mode $~\n");
			solveQuadratic();
		}
		else if((vn = Txt::contains(infix,'=')) != -1)
		{
			std::string lvalue = Txt::trimEnd(Txt::substring(infix,0,vn-1));
			int v;
			if((v = Math::isVariable(lvalue)) == -1)
			{
				printf(">>>Variable %s created\n",lvalue.c_str());
				v = Math::variables.size();
				Math::variables.push_back(new Variable(lvalue,0.0));
				variables = Math::variables;
			}
			std::string rvalue = Txt::trimFront(Txt::substring(infix,vn+1,infix.size()-1));
			double val = Math::evaluateRPN(Math::infixToRPN(rvalue),0);
			Math::variables[v]->setValue(val);
			printf("Variable edited: %s\n",Math::variables[v]->getName().c_str());
		}
		else if(substring(infix,0,3) == "def ")
		{
			std::stringstream stream;
			std::string newvar;
			double val = 0.0f;
			stream << infix;
			stream >> newvar >> newvar >> val;
			bool canCreate = true;
			for(int c = 0; c < variables.size(); c++)
			{
				if(variables[c]->getName() == newvar)
				{
					printf("-->Cannot define variable %s, it has already been defined\n",variables[c]->getName().c_str());
					canCreate = false;
					break;
				}
			}
			if(canCreate)
			{
				variables.push_back(new Variable (newvar, val));
				printf(">>>Variable %s created.\n",newvar.c_str());
			}
		}	
		else
		{
			std::string r = Math::infixToRPN(infix);
			Math::evaluateRPN(r,0);
			//printf("= %f\n", Math::evaluateRPN(r,0));
		}
		infix.clear();
		Math::rpn.str(std::string());
		std::cin.clear();
	}

	return 0;
}

void solveQuadratic()
{
	printf("Variable list size: %d\n", Math::variables.size());
	double a,b,c,x1,x2;
	int i;
	std::string ans;
	printf("Enter A value: ");
	std::cin >> ans;
	if((i = Math::isVariable(ans)) != -1) {printf("Variable found: %s\n",Math::variables[i]->getName().c_str()); a = Math::variables[i]->getValue();}
	else a = atof(ans.c_str());
	printf("Enter B value: ");
	std::cin >> ans;
	if((i = Math::isVariable(ans)) != -1) {printf("Variable found: %s\n",Math::variables[i]->getName().c_str()); b = Math::variables[i]->getValue();}
	else b = atof(ans.c_str());
	printf("Enter C value: ");
	std::cin >> ans;
	if((i = Math::isVariable(ans)) != -1) {printf("Variable found: %s\n",Math::variables[i]->getName().c_str()); c = Math::variables[i]->getValue();}
	else c = atof(ans.c_str());
	printf("Performing black magic...\n");
	if(b*b - 4 * a * c < 0)
	{
		printf("No solutions :(\n");
	}
	else if(b*b - 4 * a * c == 0)
	{
		printf("1 solution was found.\nx = ");
		x1 = -b / (2 * a);
		printf("%f\n",x1);
	}
	else
	{
		printf("2 solutions found.\n");
		x1 = (-b + sqrt(b*b-4*a*c))/(2*a);
		x2 = (-b - sqrt(b*b-4*a*c))/(2*a);
		printf("x1 = %f\nx2 = %f\n",x1,x2);
	}
	std::cin.clear();
	std::cin.ignore();
}

std::string substring(std::string s, int start, int end)
{
	std::string sub;
	for(int c = start; c <= end; c++)
		sub += s[c];
	return sub;
}
