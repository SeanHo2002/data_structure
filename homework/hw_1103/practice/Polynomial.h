#ifndef Polynomial_h
#define Polynomial_h
#include <iostream>
#include <stdio.h>
#include "Term.h"
#include <string>
using namespace std;
class Polynomial {
private:
	int term_frequency;
	int term_max;
	Term *termArr; 
public:
	Polynomial(int term=0) {
		term_frequency = term;
		term_max = 10;
		termArr = new Term[term_max];
	}
	Polynomial Add(Polynomial input_Polynomial) {
		Polynomial return_Polynomial;
		int aPos = 0, bPos = 0;
		while ((aPos < term_frequency) && (bPos < input_Polynomial.term_frequency)) {
			if (termArr[aPos].exp == input_Polynomial.termArr[bPos].exp) {
				float t = termArr[aPos].coef + input_Polynomial.termArr[bPos].coef;
				if (t)return_Polynomial.NewTerm(t, termArr[aPos].exp);
				aPos++; bPos++;
			}
			else if (termArr[aPos].exp < input_Polynomial.termArr[bPos].exp) {
				return_Polynomial.NewTerm(input_Polynomial.termArr[bPos].coef, input_Polynomial.termArr[bPos].exp);
				bPos++;
			}
			else {
				return_Polynomial.NewTerm(termArr[aPos].coef, termArr[aPos].exp);
				aPos++;
			}
		}
		for (; aPos < term_frequency; aPos++)
			return_Polynomial.NewTerm(termArr[aPos].coef, termArr[aPos].exp);
		for (; bPos < input_Polynomial.term_frequency; bPos++)
			return_Polynomial.NewTerm(input_Polynomial.termArr[bPos].coef, input_Polynomial.termArr[bPos].exp);
		return return_Polynomial;
	}
	void NewTerm(const int new_coef, const float new_exp) {
		if (term_frequency == term_max) {
			term_max *= 2;
			Term *term_carry = new Term[term_max];
			copy(termArr, termArr + term_frequency, term_carry);
			delete termArr;
			termArr = term_carry;
		}
		Term_check(new_coef, new_exp, term_frequency, termArr);
		Term_sort(term_frequency, termArr);
	}
friend ostream& operator<<(ostream& os,const Polynomial& thePoly);
friend istream& operator>>(istream& is, Polynomial& thePoly);
};
void Term_sort(const int max, Term *input_Term) {
	for (int x = 0; x < max+1; x++) {
		for (int y = x + 1; y < max+1; y++) {
			if (input_Term[x].exp < input_Term[y].exp) {
				int exp_carry = input_Term[x].exp; float coef_carry = input_Term[x].coef;
				input_Term[x].exp = input_Term[y].exp; input_Term[x].coef = input_Term[y].coef;
				input_Term[y].exp = exp_carry; input_Term[y].coef = coef_carry;
			}
		}
	}
}
void Term_check(const int input_coef, const int input_exp, int &max, Term *input_Term) {
	bool yn=true;
	for (int x = 0; x < max; x++) {
		if (input_exp == input_Term[x].exp) {
			input_Term[x].coef += input_coef;
			yn = false;
			break;
		}
		else yn = true;
	}
	if (yn) {
		input_Term[max].coef = input_coef;
		input_Term[max].exp = input_exp;
		max++;
	}
}
ostream& operator<<(ostream& os, const Polynomial& thePoly) {
	int c, e;
	string sign;
	for (int i = 0; i < thePoly.term_frequency; i++) {
		c = thePoly.termArr[i].coef;
		e = thePoly.termArr[i].exp;
		if (i > 0 && c > 0) sign = "+";
		else sign = "";
		cout << sign << "(" << c;
		if (e > 1)cout << "x^" << e;
		else if (e == 1)cout << "x";
		cout << ")";
	}
	return os;
}
istream& operator>>(istream&is, Polynomial &thePoly) {
	int num, e; float c;
	cout << "enter the num of term of poly:"; cin >> num;
	for (int x = 0; x < num; x++) {
		cout << "enter the " << x + 1 << "of the coeff:";
		cin >> c;
		cout << "enter the " << x + 1 << "of the exp:";;
		cin >> e;
		thePoly.NewTerm(c, e);
	}
	return is;
}
#endif

