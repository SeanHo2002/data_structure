#include <iostream>
#include <cstdlib>
#include <math.h>
#include "Polynomial.h"
#include "Term.h"
using namespace std;
int main(void) {
	Polynomial a, b;
	cin >> a;
	cin >> b;
	cout << "A(X)=" << a << endl;
	cout << "B(X)=" << b << endl;
	cout << "A(X)+B(X)=" << a.Add(b) << endl;
	return 0;
} 