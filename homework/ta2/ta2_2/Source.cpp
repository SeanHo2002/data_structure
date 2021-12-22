#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	int* num = new int[100000];
	ifstream readFile("rand_number_100000.txt");
	string num_carry;
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
	for (int x = 0; x < 100000; x++) {
		for (int y = x; y < 100000; y++) {
			if (num[x] > num[y]) {
				num[x] = num[x] ^ num[y]; 
				num[y] = num[x] ^ num[y]; 
				num[x] = num[x] ^ num[y];
			}
		}
	}
	ofstream newFile("after_sort.txt");
	for (int x = 0; x < 100000; x++) {
		newFile << num[x] << "\n";
		//cout << num[x] << endl;
	}
	newFile.close();
	system("pause");
	return 0;
}