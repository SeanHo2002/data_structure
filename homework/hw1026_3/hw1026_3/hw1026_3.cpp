#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int Plus[40320];
int num[8][8];
void permutation(int c[], const int x, const int y,int& t1) {
	if (x == y) {
		Plus[t1] = 0;
		for (int i = 0; i <= y; i++) {
			Plus[t1] += num[i][c[i]];
		}
		t1++;
	}
	else {
		for (int i = x; i <= y; i++) {
			swap(c[x], c[i]);
			permutation(c, x + 1, y,t1);
			swap(c[x], c[i]);
		}
	}
}
int main() {
	int time = 0;
	ifstream readFile("data.txt");
	string num_carry;
	int carry[]={0,1,2,3,4,5,6,7};
	while (true) {
		if (!readFile.is_open()) {
			cout << "Failed to open file.\n";
			break;
		}
		else {
			int x = 0, y = 0;
			for (string str; readFile >> str;) {
				num[x][y] = stoi(str);
				y += 1;
				if (y == 8){
					x += 1;
					y = 0;
				}
			}
			break;
		}
	}
	permutation(carry, 0, 7,time);
	int big = 0;
	for (int i = 0; i < 40320; i++) {
		if (Plus[i] > big)
			big = Plus[i];
	}
	cout << big << endl;
	system("pause");
	return 0;
}