#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
int main() {
	srand(time(NULL));
	ofstream newFile;
	int rst;
	newFile.open("rand_number_100000.txt");
	int *x=new int[100000],time=0;
	for (int y = 0; y < 100000; y++) {
		rst = (rand() << 15) | rand();
		x[y] = rst % (200000 - 1 + 1) + 1;
	}
	for (int y = 0; y < 100000; y++) {
		newFile << x[y] << "\n";
		time++;
	}
	newFile << "總共" << time << "組資料\n";
	newFile.close();
	system("pause");
	return 0;
}