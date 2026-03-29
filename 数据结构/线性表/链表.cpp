#include <iostream>
using namespace std;
template <typename T>
struct Node {
	T data;
	Node* next;
};
template <typename T>
class List {
public:
	List() {
		count = 0;
		front = new Node;
		front->next = NULL;
		rear = front;
	};
	~List() {
		while (Length() != 0) {
			Delete_element();
		}
		delete front;
	};
	int Length()const {
		Node* p = front->next;
		int n;
		while (p != NULL) {
			n++;
			p = p->next;
		}
		return n;
	}
	bool Get_element(const int i, T& x)const {
		Node* p = front->next;
		int n = 1;
		while (p != NULL && n != i) {
			p = p->next;
			n++;
		}
		if (p == NULL) {
			return false;
		}
		x = p->data;
		return true;
	};
	Node* Locate(const T& x) {
		p = front->next;
		while (p != NULL || p->data != x) {
			p = p->next;
		}
		if (p == NULL) {
			return NULL;
		}
		x = p->data;
		return p;
	};
	bool Insert(const int i, const T x) {
		p = front;
		int n = 0;
		if (i<0 || i>count+1) {
			return false;
		}
		while (n != i - 1 && p != NULL) {
			p = p->next;
			n++;
		}
		if (p == NULL) {
			return false;
		}
		Node* s = new Node;
		s->next = p->next;
		s->data = x;
		p->next = s;
		cout++;
		return true;
	};
	bool Delete_element(const int i) {
		p = front;
		int n = 0;
		if (i<0 || i>count) {
			return false;
		}
		while (p != NULL && n != i-1) {
			p = p->next;
			n++;
		}
		if (p == NULL || p->next = NULL) {
			return false;
		}
		Node* q = p->next;
		p->next = q->next;
		delete q;
		count--;
		return true;
	};
	void createfromhead(){
		cin >> x;
		while (x != 9999) {
			Node* s = new Node;
			s->data = x;
			s->next = front->next;
			front->next = s;
			cin >> x;
		}
	}
	void createfromtail() {
		cin >> x;
		while (x!=9998){
			Node* s = new Node;
			s->data = x;
			rear->next = s;
			rear = s;
			rear->next = NULL;
			cin >> x;
		}
	}
private:
	int coount;
	Node* front;
	Node* rear;
};