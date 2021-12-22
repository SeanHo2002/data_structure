#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
typedef struct Locate {
	int x, y;
};
template <class T>
class Stacks {
private:
	T* arr;
	int capacity, top;
public:
	Stacks(int cap = 10) {
		capacity = cap;
		arr = new T[capacity];
		top = 0;
	}
	~Stacks() {
		delete[]arr;
	}
	int Size() {
		return top;
	}
	bool IsEmpty() {
		if (top != 0)
			return false;
		else
			return true;
	}
	T Top() {
		if (IsEmpty()) {
			Locate re;
			re.x = 0; re.y = 0;
			return re;
		}
		else
			return arr[top - 1];
	}
	void Push(const T item) {
		if (top == capacity) {
			capacity *= 2;
			T* carry = new T[capacity];
			for (int x = 0; x < top; x++)
				carry[x] = arr[x];
			delete[]arr;
			arr = new T[capacity];
			for (int x = 0; x < top; x++)
				arr[x] = carry[x];
		}
		arr[top++] = item;
	}
	T Pop() {
		if (IsEmpty())
			cout << "stacks is empty" << endl;
		else {
			T carry = arr[top - 1];
			top--;
			return carry;
		}
	}
};
enum directions{N,NE,E,SE,S,SW,W,NW};//上,右上,右,右下,下,左下,左,左上
int move_x[8] = { 0,1,1,1,0,-1,-1,-1 };
int move_y[8] = { -1,-1,0,1,1,1,0,-1 };
int maze[100][100];
char maze_out[100][100];
void GetMaze(int r,int c) {
	ifstream ifs;
	char buffer[100];
	int x = 0;
	ifs.open("maze_row_13_col_17.txt");
	if (!ifs.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		while (!ifs.eof()) {
			ifs.getline(buffer, sizeof(buffer));
			for (int y = 0; y < c; y++) {
				maze[x][y] = (int)buffer[y] - 48;
				maze_out[x][y] = buffer[y];
			}
			x++;
		}
		ifs.close();
		for(int x=0;x<r;x++){
			for (int y = 0; y < c; y++) {
				cout << maze[x][y];
			}
			cout << endl;
		}
	}
}
int main() {
	int row=13, col=17;
	Locate locate;
	bool IsDeadEnd=true;
	locate.x = 1; locate.y = 1;
	Stacks<Locate> stack;
	GetMaze(row, col);
	while (true) {
		if (locate.x == 15 && locate.y == 11) {
			maze_out[11][15] = '*';
			break;
		}
		for (int i = 0; i < 8; i++) {
			IsDeadEnd = true;
			if (maze[locate.y + move_y[i]][locate.x + move_x[i]] == 0) {
				/*Locate carry = stack.Top();
				if (locate.x + move_x[i] == carry.x && locate.y + move_y[i] == carry.y) {
					continue;
				}*/
				maze[locate.y][locate.x] = 1;
				stack.Push(locate);
				locate.x += move_x[i];
				locate.y += move_y[i];
				IsDeadEnd = false;
				//cout << "x:" << locate.x << ",y:" << locate.y << endl;
				break;
			}
		}
		if (IsDeadEnd) {
			maze[locate.y][locate.x] = 1;
			locate = stack.Pop();
		}
	}
	Stacks<Locate> out_carry;
	while (!stack.IsEmpty()) {
		Locate out = stack.Pop();
		out_carry.Push(out);
		maze_out[out.y][out.x] = '*';
	}
	while (!out_carry.IsEmpty()) {
		Locate out = out_carry.Pop();
		cout << "x:" << out.x << ",y:" << out.y << endl;
	}
	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			cout << maze_out[x][y];
		}
		cout << endl;
	}
}
/*cout << "input row:";
cin >> row;
cout << "input col:";
cin >> col;*/