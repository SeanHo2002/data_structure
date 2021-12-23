#include <iostream>
#include <string>
using namespace std;
template <class T>
class Linked {
private:
	class Node {
		friend Linked;
	private:
		T value;
		Node* nextNode;
	};
	Node* first;
	Node* last;
public:
	Linked() {}
	void Add(T in) {
		if (!first) {
			first = new Node();
			first->value = in;
			last = first;
		}
		else {
			last->nextNode = new Node();
			last = last->nextNode;
			last->value = in;
		}
	}
	void Remove(T in) {
		Node* locate = first;
		while (locate) {
			if (locate != last) {
				if ((locate->nextNode)->value == in) {
					if (locate->nextNode == last) {
						locate->nextNode=last->nextNode;
						last = locate;
						break;
					}
					else {
						locate->nextNode = (locate->nextNode)->nextNode;
						break;
					}
				}
			}
			locate = locate->nextNode;
		}
	}
	void Reverse() {
		Node* locate = first;
		Node* front = locate->nextNode;
		Node* back;
		while(front->nextNode != last){
			back = locate;
			locate = front;
			front = front->nextNode;
			locate->nextNode = back;
		}
		(front->nextNode)->nextNode = front;
		front->nextNode = locate;
		Node* carry = last;
		last = first;
		first = carry;
	}
	void PrintAll() {
		Node* locate = first;
		while (locate!=last) {
			cout << locate->value << ",";
			locate = locate->nextNode;
		}
		cout << last->value << endl;
	}
};
int main(void) {
	Linked<int> linked;
	for (int x = 1; x <= 20; x++)
		linked.Add(x);
	linked.PrintAll();
	for (int x = 2; x <= 20; x += 2)
		linked.Remove(x);
	linked.PrintAll();
	linked.Reverse();
	linked.PrintAll();
}