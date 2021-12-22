#include <iostream>
#include <cstdlib>
#include <math.h>
#include "Rational.h"
using namespace std;
int main(void) {
	Rational b;
	Rational a(1, 3);           // a=1/3
	cin >> b;
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << (a / b) << endl;
}