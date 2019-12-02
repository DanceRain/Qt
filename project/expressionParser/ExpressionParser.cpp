#include "ExpressionParser.h"
#include <stdexcept>

double anaExpression(const string& exp, string::iterator& pos)
{
	double result = anaTerm(exp, pos);
	while (pos != exp.end())
	{
		char op = *pos;
		if (op != '+' && op != '-')
		{
			return result;
		}
		++pos;
		double term = anaTerm(exp, pos);
		if(op == '+')
		{
			result += term;
		}
		if (op == '-')
		{
			result -= term;
		}
	}
	return result;
}

 double anaTerm(const string& exp, string::iterator& pos)
{
	double result = anaFactor(exp, pos);
	while (pos != exp.end())
	{
		char op = *pos;
		if (op != '*' && op != '/')
		{
			return result;
		}
		++pos;
		double term = anaFactor(exp, pos);
		if (op == '*')
		{
			result *= term;
		}
		if (op == '/')
		{
			if (term != 0)
			{
				result /= term;
			}
			else
			{
				throw std::runtime_error("the dividend can't be zero!");
			}
		}
	}
	return result;
}

double anaFactor(const string& exp, string::iterator& pos)
{
	double result;
	bool negative = false;

	if (*pos == '-')
	{
		negative = true;
	}
	if (*pos == '(')
	{
		++pos;
		result = anaExpression(exp, pos);
		if (*pos != ')')
		{
			throw std::runtime_error("the expression has wrong");
		}
		++pos;
	}
	else
	{
		string token;
		while (pos != exp.end() && (isdigit(*pos) || *pos == '.'))
		{
			token.push_back(*pos);
			++pos;
		}
		result = atof(token.c_str());
	}
	if (negative)
	{
		result = -result;
	}
	return result;
}
