#pragma once
#include <string>
using std::string;
double anaExpression(const string& exp, string::iterator& pos);
double anaTerm(const string& exp, string::iterator& pos);
double anaFactor(const string& exp, string::iterator& pos);
