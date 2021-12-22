#ifndef Rational_h
#define Rational_h
#include <stdio.h>
#include <iostream>
using namespace std;
class Rational {
friend istream& operator>>(istream& is, Rational& r);
private:
	float a, b;
public:
	Rational(float in_a = 0, float in_b = 0) {
		a = in_a; b = in_b;
	}
	float operator+(Rational & r) {
		return((a/b) + (r.a/r.b));
	}
	float operator-(Rational& r) {
		return((a / b) - (r.a / r.b));
	}
	float operator*(Rational& r) {
		return((a / b) * (r.a / r.b));
	}
	float operator/(Rational& r) {
		return((a / b) / (r.a / r.b));
	}
};
istream& operator>>(istream& is, Rational& r) {
	char c;
	cout << "輸入有理數:";
	is >> r.a >> c >> r.b;
	return is;
}
#endif