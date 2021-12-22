#ifndef Polynomial_h
#define Polynomial_h
#include <stdio.h>
#include "Term.h"
#include <iostream>
#include <string>
using namespace std;
class Polynomial {
private:
	Term *termArray;
	int capacity,terms;
public:
	Polynomial(int numTern=0) {
		terms = numTern;
		capacity = 10;//x最大次方
		termArray = new Term[capacity];
	}
	Polynomial Add(Polynomial b){
		Polynomial c;
		int aPos = 0, bPos = 0;
		while ((aPos < terms) && (bPos < b.terms)) {
			if (termArray[aPos].exp == b.termArray[bPos].exp) {
				float t = termArray[aPos].coef + b.termArray[bPos].coef;
				if (t)c.NewTerm(t, termArray[aPos].exp);
				aPos++; bPos++;
			}
			else if (termArray[aPos].exp < b.termArray[bPos].exp) {
				c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
				bPos++;
			}
			else {
				c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		}
		for (; aPos < terms; aPos++)
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		for (; bPos < b.terms; bPos++)
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
		return c;
	}
	void NewTerm(const float theCoeff, const int theExp) {
		if (terms == capacity) {
			capacity *= 2;
			Term *temp = new Term[capacity];
			copy(termArray, termArray + terms, temp);
			delete[] termArray;
			termArray = temp;
		}
		termArray[terms].coef = theCoeff;
		termArray[terms++].exp = theExp;
	}
	friend istream& operator>>(istream& input, const Polynomial& thePoly);
	friend ostream& operator<<(ostream& output, const Polynomial& thePoly);
};
ostream& operator<<(ostream& output, const Polynomial& thePoly) {
	int c, e;
	string sign;
	for (int i = 0; i < thePoly.terms; i++) {
		c = thePoly.termArray[i].coef;
		e = thePoly.termArray[i].exp;
		if (i > 0 && c > 0) sign = "+";
		else sign = "";
		cout << sign << "(" <<c;
		if (e > 1)cout << "x^" << e;
		else if (e == 1)cout << "x";
		cout << ")";
	}
	return output;
}
istream& operator>>(istream& input, Polynomial& thePoly) {
	int numTerms, e;
	float c;
	cout << "enter the num of term of poly:";
	cin >> numTerms;
	for (int i = 0; i < numTerms; i++) {
		cout << "enter the " << i << "of the coeff:";
		cin >> c;
		cout << "enter the " << i << "of the exp:";;
		cin >> e;
		thePoly.NewTerm(c, e);
	}
	return input;
}
#endif