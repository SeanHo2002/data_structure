/*#include <iostream>
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
	cout << a / b << endl;
}*/
#include <iostream>
#include <fstream>
using namespace std;
void pbv(int num1) {
	num1 = 5;
	cout << "in pass by value:" << num1 << endl;
}
void pbr(int& num1) {
	num1 = 5;
	cout << "in pass by reference:" << num1 << endl;
}
void pbcr(const int& num1) {
	cout << "in pass by constant reference:" << num1 << endl;
}
int main() {
	int num = 10;
	cout << "before pass by value:" << num << endl;
	pbv(num);
	cout << "after pass by value:" << num << endl;
	num = 10;
	cout << "before pass by reference:" << num << endl;
	pbr(num);
	cout << "after pass by reference:" << num << endl;
	num = 10;
	cout << "before pass by constant reference:" << num << endl;
	pbcr(num);
	cout << "after pass by constant reference:" << num << endl;
	system("pause");
	return 0;
}