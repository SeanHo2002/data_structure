#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
int Fibonacci(int num) {
	if (num == 0)
		return 0;
	else if (num == 1)
		return 1;
	else
		return(Fibonacci(num - 1) + Fibonacci(num - 2));
}
int main(void) {
	int value;
	while (true) {
		cout << "��J�@��:"; cin >> value;
		cout << "Fibonacci Number:" << Fibonacci(value) << endl;
	}
}