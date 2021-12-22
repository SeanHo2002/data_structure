#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
void changePtr1(int** refPInt) {
	int in = 0;
	cout << "------before------" << endl;
	cout << "**refPInt:" << **refPInt << endl;
	cout << "*refPInt:" << *refPInt << endl;
	cout << "refPInt:" << refPInt << endl;
	*refPInt = &in;
	cout << "------after------" << endl;
	cout << "**refPInt:" << **refPInt << endl;
	cout << "*refPInt:" << *refPInt << endl;
	cout << "refPInt:" << refPInt << endl;
}
void changePtr2(int*& refPInt) {
	int in = 0;
	refPInt = &in;
}
int main(void) {
	int localInt = 1;
	int* localPInt = &localInt;
	changePtr1(&localPInt);
	changePtr2(localPInt);
	cout << localPInt << endl;;
	return 0;
}