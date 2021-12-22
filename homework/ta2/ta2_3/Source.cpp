#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int* num = new int[100000];
int carry;
void bsa(int fnum, int snum, int left, int right) {
	if (fnum == num[snum])
		cout << "在第" << snum + 1 << "行" << endl;
	else if(carry== (left + snum) / 2|| carry == (right + snum) / 2)
		cout << "無此數" << endl;
	else if (fnum < num[snum]) {
		carry=(left + snum) / 2;
		bsa(fnum, (left + snum) / 2, left, snum);
	}
	else if (fnum > num[snum]) {
		carry = (right + snum) / 2;
		bsa(fnum, (right + snum) / 2, snum, right);
	}
}
int main() {
	int enter_num;
	ifstream readFile("after_sort.txt");
	string num_carry;
	cout << "enter a number:";
	cin >> enter_num;
	if (!readFile.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		for (int x = 0; x < 100000; x++) {
			getline(readFile, num_carry);
			num[x] = stoi(num_carry);
			//cout << num[x] << endl;
		}
	}
	bsa(enter_num, 100000 / 2, 0, 100000);
	system("pause");
	return 0;
}