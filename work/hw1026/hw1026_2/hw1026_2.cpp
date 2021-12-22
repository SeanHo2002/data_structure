#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
int Ackerman(int m, int n) {
	if (m == 0)
		return(n + 1);
	else if (n == 0)
		return(Ackerman(m - 1, 1));
	else
		return(Ackerman(m - 1, Ackerman(m, n - 1)));
}
int main(void) {
	int value1, value2;
	while (true) {
		cout << "m:"; cin >> value1; cout << "n:"; cin >> value2;
		cout << "Ackerman's Number:" << Ackerman(value1, value2) << endl;
	}
}