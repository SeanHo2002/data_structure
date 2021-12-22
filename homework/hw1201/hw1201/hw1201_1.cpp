#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
int in = 0, in1 = 3;
void changePtr1(int** refPInt) {
	cout << "------before------" << endl;
	cout << "**refPInt:" << **refPInt << endl;
	cout << "*refPInt:" << *refPInt << endl;
	cout << "refPInt:" << refPInt << endl;
	*refPInt = &in;
	cout << "------after------" << endl;
	cout << "in address:" << *refPInt << endl;
	cout << "**refPInt:" << **refPInt << endl;
	cout << "*refPInt:" << *refPInt << endl;
	cout << "refPInt:" << refPInt << endl;
}
void changePtr2(int*& refPInt) {
	cout << "------before------" << endl;
	cout << "*&refPInt:" << refPInt << endl;
	refPInt = &in1;
	cout << "------after------" << endl;
	cout << &in1 <<endl<< "*&refPInt:" << refPInt << endl;
}
int main(void) {
	int localInt = 1;
	int* localPInt = &localInt;
	cout << "localInt address:" << &localInt << endl << "localPInt value:" << localPInt << endl << "localPInt address:" << &localPInt << endl;
	changePtr1(&localPInt);
	cout << endl;
	cout << "localInt address:" << &localInt << endl << "localPInt value:" << localPInt << endl << "localPInt address:" << &localPInt << endl;
	changePtr2(localPInt);
	return 0;
}