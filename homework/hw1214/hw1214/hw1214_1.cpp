#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
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
		if (IsEmpty())
			return -1;
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
			arr[top--] = '\0';
			return carry;
		}
	}
	void Show() {
		cout << "[";
		for (int x = 0; x < top; x++) {
			cout << arr[x];
			if (x != top - 1)
				cout << ",";
		}
		cout << "]" << endl;
	}
	string get() {
		if (IsEmpty())
			return "empty";
		else {
			string re = "";
			for (int x = 0; x < top; x++)
				re += arr[x];
			return re;
		}
	}
};
int icp(char in) {//out stock
	switch (in) {
	case '+':
		return 12;
	case '-':
		return 12;
	case '*':
		return 13;
	case '/':
		return 13;
	case '%':
		return 13;
	case '(':
		return 20;
	}
}
int isp(char in) {//in stock
	switch (in) {
	case '+':
		return 12;
	case '-':
		return 12;
	case '*':
		return 13;
	case '/':
		return 13;
	case '%':
		return 13;
	case '(':
		return 0;
	}
}
int main() {
	string in, out = "";
	Stacks<char> stack;
	Stacks<int> stack_count;
	cout << "input:";
	cin >> in;
	cout << "------------------------------------" << endl;
	cout << left << setw(15) << "next token" << left << setw(10) << "stack" << left << setw(11) << "output" << endl;
	cout << "------------------------------------" << endl;
	for (int x = 0; x < in.length(); x++) {
		if (in[x] == ')') {
			while (true) {
				char carry = stack.Pop();
				if (carry == '(')
					break;
				else {
					out += carry;
					out += ",";
				}
			}
		}
		else if (in[x] == '+' || in[x] == '-' || in[x] == '*' || in[x] == '/' || in[x] == '%' || in[x] == '(') {
			while (true) {
				if (icp(in[x]) <= isp(stack.Top())) {
					out += stack.Pop();
					out += ",";
				}
				else {
					stack.Push(in[x]);
					break;
				}
			}
		}
		else if ((int)in[x] - 48 >= 0 && (int)in[x] - 48 <= 9) {
			int carry=0;
			while ((int)in[x] - 48 >= 0 && (int)in[x] - 48 <= 9) {
				carry *= 10;
				carry += in[x++] - 48;
			}
			x--;
			out += to_string(carry);
			out += ",";
		}
		cout << left << setw(15) << in[x] << left << setw(10) << stack.get() << left << setw(11) << out << endl;
	}
	if (!stack.IsEmpty()) {
		int carry = stack.Size();
		for (int y = 0; y < carry; y++) {
			out += stack.Pop();
			out += ",";
			cout << left << setw(15) << "none" << left << setw(10) << stack.get() << left << setw(11) << out << endl;
		}
	}
	cout << "------------------------------------" << endl;
	cout << "output:" << out << endl;
	for (int x = 0; x < out.length(); x++) {
		if ((int)out[x] - 48 >= 0 && (int)out[x] - 48 <= 9) {
			int carry = 0;
			while (out[x] != ',') {
				carry *= 10;
				carry += out[x++] - 48;
			}
			stack_count.Push(carry);
		}
		else {
			int num1=stack_count.Pop(), num2 = stack_count.Pop();
			switch ((char)out[x]) {
				case '+':
					stack_count.Push(num2 + num1);
					break;
				case '-':
					stack_count.Push(num2 - num1);
					break;
				case '*':
					stack_count.Push(num2 * num1);
					break;
				case '/':
					stack_count.Push(num2 / num1);
					break;
				case '%':
					stack_count.Push(num2 % num1);
					break;
			}
			x++;
		}
	}
	while(!stack_count.IsEmpty())
		cout <<"Answer:"<< stack_count.Pop();
	return 0;
}