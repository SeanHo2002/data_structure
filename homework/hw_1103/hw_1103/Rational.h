#ifndef Rational_h
#define Rational_h
#include <stdio.h>
#include <iostream>
using namespace std;
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a%b);
}
class Rational {
friend istream& operator>>(istream& is, Rational& r);
friend ostream& operator<<(ostream& os, Rational& r);
private:
	int a, b;
	int f_a, f_b;
public:
	Rational(int in_a = 0, int in_b = 0, int in_fa=0, int in_fb=0) {
		a = in_a; b = in_b;
		f_a = in_fa; f_b = in_fb;
	}
	Rational &operator+(Rational & r) {
		r.f_b = b * r.b;
		r.f_a = (a*r.b) + (r.a*b);
		int in_gcd = gcd(r.f_a, r.f_b);
		r.f_a /= in_gcd;
		r.f_b /= in_gcd;
		return(r);
	}
	Rational &operator-(Rational& r) {
		r.f_b = b * r.b;
		r.f_a = (a*r.b) - (r.a*b);
		int in_gcd = gcd(r.f_a, r.f_b);
		r.f_a /= in_gcd;
		r.f_b /= in_gcd;
		return(r);
	}
	Rational &operator*(Rational& r) {
		r.f_b = b * r.b;
		r.f_a = a * r.a;
		int in_gcd = gcd(r.f_a, r.f_b);
		r.f_a /= in_gcd;
		r.f_b /= in_gcd;
		return(r);
	}
	Rational &operator/(Rational& r) {
		r.f_b = b * r.a;
		r.f_a = a*r.b;
		int in_gcd = gcd(r.f_a, r.f_b);
		r.f_a /= in_gcd;
		r.f_b /= in_gcd;
		return(r);
	}
};
istream& operator>>(istream& is, Rational& r) {
	char c;
	cout << "輸入有理數:";
	is >> r.a >> c >> r.b;
	return is;
}
ostream& operator<<(ostream& os, Rational& r) {
	if(pow(r.f_a,2) >= pow(r.f_b,2)) {
		int c = r.f_a / r.f_b;
		r.f_a %= r.f_b;
		if(r.f_a ==0)
			os << c;
		else
			os << c << "+" << r.f_a << "/" << r.f_b;
	}
	else
		os << r.f_a << "/" << r.f_b;
	return os;
}
#endif