#ifndef Term_h
#define Term_h
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
class Polynomial;
class Term {
	friend ostream& operator<<(ostream& os, const Polynomial& thePoly);
	friend istream& operator>>(istream& is, Polynomial& thePoly);
	friend Polynomial;
	friend void Term_sort(int, Term*);
	friend void Term_check(int,int,int&, Term*);
private:
	int exp;
	float coef;
};
#endif
