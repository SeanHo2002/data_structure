#include <iostream>
#include <fstream>
using namespace std;
int main() {
	int x = 5, y = 6;
	cout << "before change" << endl;
	cout << "x=" << x << endl << "y=" << y << endl;
	cout << "after change" << endl;
	x = x ^ y; y = x ^ y; x = x ^ y;
	cout << "x=" << x << endl << "y=" << y << endl;
	system("pause");
	return 0;
}