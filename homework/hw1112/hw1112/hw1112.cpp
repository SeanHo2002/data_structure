#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class SparseMatrix;
class MatrixTerm {
friend SparseMatrix;
private:
	int row, col, value;
};
class SparseMatrix {
private:
	int row, col, terms, capacity;
	MatrixTerm* smArr;	
public:
	SparseMatrix(int r, int c,int n) {
		terms = 0; row = r; col = c; capacity = n;
		smArr = new MatrixTerm[capacity];
	}
	void Add(int r, int c, int v) {
		smArr[terms].row = r;
		smArr[terms].col = c;
		smArr[terms].value = v;
		terms += 1;
	}
	void Set(int t, int r,int c, int v) {
		smArr[t].row = r;
		smArr[t].col = c;
		smArr[t].value = v;
	}
	void Show() {
		for (int x = 0; x < terms; x++) {
			cout << "[" << x << "]  " << smArr[x].row << "  " << smArr[x].col << "  " << smArr[x].value << endl;
		}
	}
	void ShowMatrix() {
		int term = 0; bool check = true;
		for (int x = 0; x < row; x++) {
			for (int y = 0; y < col; y++) {
				for (int z = 0; z < capacity; z++) {
					check = true;
					if (smArr[z].row == x && smArr[z].col==y) {
						cout << smArr[z].value << " ";
						check = false;
						break;
					}
				}
				if(check)
					cout << "0 ";
			}
			cout << endl;
		}
	}
	void method1() {
		SparseMatrix a(col, row, capacity);
		for (int x = 0; x < col; x++)
			for (int y = 0; y < terms; y++)
				if (smArr[y].col == x)
					a.Add(smArr[y].col, smArr[y].row, smArr[y].value);
		cout << "matrix transpose method1:" << endl;
		a.Show();
	}
	void method2() {
		int *row_terms=new int[col];
		int *start=new int[col];
		for (int x = 0; x < col; x++) {
			row_terms[x] = 0;
			start[x] = 0;
		}
		for (int x = 0; x < col; x++)
			for (int y = 0; y < terms; y++)
				if (smArr[y].col == x)
					row_terms[x] += 1;
		for (int x = 1; x < col; x++)
			start[x] = start[x - 1] + row_terms[x - 1];
		SparseMatrix a(col, row, capacity);
		for (int x = 0; x < terms; x++)
				a.Add(0, 0, 0);
		for (int x = 0; x < terms; x++) {
			a.Set(start[smArr[x].col], smArr[x].col, smArr[x].row, smArr[x].value);
			start[smArr[x].col]++;
		}
		cout << "matrix transpose method2:" << endl;
		a.ShowMatrix();
	}
};
int main() {
	ifstream readFile("data.txt");
	int rm, cm,nonzero;
	cout << "enter row max:"; cin >> rm;
	cout << "enter colmax:"; cin >> cm;
	cout << "enter nonzero:"; cin >> nonzero;
	SparseMatrix a(rm, cm, nonzero);
	if (!readFile.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		int in_r = 0, in_c = 0;
		for (string str; readFile >> str;) {
			if (stoi(str)!=0) {
				a.Add(in_r, in_c, stoi(str));
			}
			in_c += 1;
			if (in_c == cm) {
				in_r += 1;
				in_c = 0;
			}
		}
	}
	a.Show();
	a.method1();
	a.method2();
	system("pause");
	return 0;
}