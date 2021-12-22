#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
template <class T>
class Queues {
private:
	T* arr;
	int capacity, front, rear;
public:
	Queues(int cap = 10) {
		capacity = cap;
		arr = new T[capacity];
		front = 0; rear = -1;
	}
	~Queues() {
		delete[]arr;
	}
	T Front() {
		return arr[front];
	}
	T Rear() {
		return arr[rear];
	}
	void Push(const T item) {
		rear += 1;
		rear %= capacity;
		arr[rear] = item;
	}
	void Pop() {
		arr[front] = '\0';
		front += 1;
		front %= capacity;
	}
	void Show() {
		cout << "[";
		for (int x = 0; x < capacity; x++) {
			cout << arr[x];
			if(x != capacity-1)
				cout << ",";
		}
		cout << "]" << endl;
	}
};
int main(void) {
	Queues<char> test(5);
	cout << "push A>push B>push C>push D>push E:";
	test.Push('A');
	test.Push('B');
	test.Push('C');
	test.Push('D');
	test.Push('E');
	test.Show();
	cout << "Front:" << test.Front() << ",Rear:" << test.Rear() << endl << endl;

	cout << "pop>pop:";
	test.Pop();
	test.Pop();
	test.Show();
	cout << "Front:" << test.Front() << ",Rear:" << test.Rear() << endl << endl;

	cout << "push F>push G:";
	test.Push('F');
	test.Push('G');
	test.Show();
	cout << "Front:" << test.Front() << ",Rear:" << test.Rear() << endl << endl;
	return 0;
}