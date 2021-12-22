#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
	ifstream readFile("data.txt");
	string num_carry;
	int* num = new int[100];
	int b1=0, b2=0,carry;
	if (!readFile.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		int x = 0;
		for (string str; readFile >> str;) {
			//cout << str << endl;
			num[x] = stoi(str);
			x++;
		}
	}
	for (int y = 0; y < 100; y++) {
		if (num[y] > b1) {
			carry = y;
			b1 = num[y];
		}
		else if (num[y] > b2 && y != carry)
			b2 = num[y];
	}
	cout << b1 << "+" << b2 << "=" << b1 + b2;
	system("pause");
	return 0;
}