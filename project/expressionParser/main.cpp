#include <iostream>
#include <string>
#include "ExpressionParser.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

void test_1(string::iterator& pos)
{
	void test_2(string::iterator& pos);
	test_2(pos);
	cout << *pos << endl;
}

void test_2(string::iterator& pos)
{
	pos++;
}

int main()
{
	string str("(1+2+3+4)*(1+2)");
	auto begin = str.begin();
	double result = anaExpression(str, begin);
	cout << result << endl;
	return 0;
}



