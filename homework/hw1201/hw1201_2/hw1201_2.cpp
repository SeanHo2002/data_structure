#include <iostream>
#include <cstdlib>
#include <math.h>
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
		if (top!=0)
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
	void Pop() {
		if (IsEmpty())
			cout << "stacks is empty" << endl;
		else
			arr[top--] = '\0';
	}
	void Show() {
		cout << "[";
		for (int x = 0; x < top; x++) {
			cout << arr[x] ;
			if (x != top - 1)
				cout << ",";
		}
		cout << "]" << endl;
	}
};
int main(void) {
	Stacks<float> test;
	cout << "Is stack empty:" << test.IsEmpty() << endl;
	cout << "push 1>push 2>push 3:";
	test.Push(1);
	test.Push(2);
	test.Push(3);
	test.Show();
	cout << "stack's size:" << test.Size() << endl << "stack's top:" << test.Top() << endl;
	cout << "Is stack empty:" << test.IsEmpty() << endl << endl;

	cout << "pop>pop:";
	test.Pop();
	test.Pop();
	test.Show();
	cout << "stack's size:" << test.Size() << endl << "stack's top:" << test.Top() << endl;
	cout << "Is stack empty:" << test.IsEmpty() << endl << endl;

	cout << "pop:";
	test.Pop();
	test.Show();
	cout << "stack's size:" << test.Size() << endl << "stack's top:" << test.Top() << endl;
	cout << "Is stack empty:" << test.IsEmpty() << endl << endl;
	return 0;
}