#include <iostream>
using namespace std;
struct Node {
	wchar_t data;
	Node* next;
};
class Stack {
public:
	Stack() {
		count = 0;
		top = NULL;
	}
	~Stack() {
		while (!Empty()) {
			Pop();
		}
	}
	bool Empty() {
		if (count == 0) {
			return true;
		}
		return false;
	}
	bool Push(const char c) {
		Node* s = new Node;
		s->data = c;
		s->next = top;
		count++;
		top = s;
		return true;
	}
	bool Pop() {
		if (Empty()) {
			return false;
		}
		Node* p = top;
		top = top->next;
		delete p;
		count--;
		return true;
	}
	char Get_top(char& c) {
		c = top->data;
		return c;
	}
private:
	int count;
	Node* top;
};
int main() {
	Stack s;
	string str;
	cin >> str;
	long long c;
	c= str.size();
	for (long long i = 0; i < c; i++) {
		s.Push(str[i]);
	}
	for (long long i = 0; i < c; i++) {
		char ch;
		s.Get_top(ch);
		cout << ch;
		s.Pop();
	}
	return 0;
}