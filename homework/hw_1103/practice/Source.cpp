#include <iostream>
#include <stdio.h>
#include "Polynomial.h"
using namespace std;
int main(void) {
	Polynomial a,b;
	cin >> a >> b;
	cout << "A(X)=" << a << endl;
	cout << "B(X)=" << b << endl;
	cout << "A(X)+B(X)=" << a.Add(b) << endl;
}