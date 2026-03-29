#include <iostream>
using namespace std;
class circularqueue {
private:
	int maxlen;
	int count;
	int front, rear;
	int data[8];
public:
	circularqueue() {
		count = 0;
		rear = front = 0;
		maxlen = 8;
	}
	bool isfull() {
		if ((rear + 1) % maxlen == front) {
			return true;
		}
		return false;
	}
	bool isempty() {
		if (front == rear) {
			return true;
		}
		return false;
	}
	bool enqueue(int x) {
		if (isfull()) {
			return false;
		}
		rear = (rear + 1) % maxlen;
		data[rear] = x;
		count++;
		return true;
	}
	bool dequeue(int& x) {
		if (isempty()) {
			return false;
		}
		front = (front + 1) % maxlen;
		x = data[front];
		count--;
		return true;
	}
	void display() {
		int i = (front+1)%maxlen;
		cout << "队列元素为：";
		while(i!=(rear+1)%maxlen){
			cout << data[i] << " ";
			i = (i + 1) % maxlen;
		}
		cout << endl;
	}
};
int main() {
	circularqueue q;
	int a[100];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		if (!q.enqueue(a[i])) {
			int temp = a[i];
			cout << "队列已满，无法入队，";
			q.dequeue(temp);
			cout << "出队元素为" << temp << endl;
			q.enqueue(a[i]);//在出队的时候没有及时把后面的数入队。
		}
		q.display();//输出当前队列元素应该是每一次数字要进来之后的队列元素。
	}
	return 0;
}