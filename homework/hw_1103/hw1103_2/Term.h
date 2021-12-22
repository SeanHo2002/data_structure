#ifndef Term_h
#define Term_h
#include <stdio.h>
#include <iostream>
using namespace std;
class Polynomial;
class Term {
	friend istream& operator>>(istream& input, const Polynomial& thePoly);
	friend ostream& operator<<(ostream& output, const Polynomial& thePoly);
	friend Polynomial;
private:
	int exp;
	float coef;
public:
};
#endif