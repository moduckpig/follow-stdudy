#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Stack {
public:
	Stack() {
		count = 0;
		top = -1;
	};
	bool Empty()const {
		if (count == 0) {
			return true;
		}
		return false;
	};
	bool Full()const {
		if (count == 100) {
			return true;
		}
		return false;
	};
	bool Push(const T& x) {
		if (Full()) {
			return false;
		}
		top++;
		data[top] = x;
		count++;
		return true;
	};
	bool Pop(T& x) {
		if (Empty()) {
			return false;
	    }
		x = data[top];
		top--;
		count--;
		return true;
	};
	T Top()const {
		return data[top];
	}
private:
	int count;
	T data[100];
	int top;
};
int priority(char x) {
	if (x == '*' || x == '/') {
		return 2;
	}
	else if (x == '+' || x == '-') {
		return 1;
	}
	else if (x == '(') {
		return 0;
	}
	return -1;
}
int main() {
	Stack<double> s;
	Stack<char> sl;
	string x;
	cin >> x;
	int len = x.length();
	for (int i = 0; i < len; i++) {
		if (x[i] >= '0' && x[i] <= '9') {
			double num = 0;
			while (i < len && x[i] >= '0' && x[i] <= '9') {
				num = num * 10 + (x[i] - '0');
				i++;
			}
			i--;
			s.Push(num);
			cout << "数字：" << num << "成功入栈" << endl;
		}
		else if (x[i] == '(') {
			sl.Push(x[i]);
			cout << "左括号（成功入栈" << endl;
		}
		else if (x[i] == ')') {
			while (!sl.Empty() && sl.Top() != '(') {
				char h ;
				sl.Pop(h);
				cout << "运算符" << h << "成功出栈" << endl;
				double a, b;
				s.Pop(b);
				s.Pop(a);
				double result;
				switch (h) {
				case '+':
					result = a + b;
					break;
				case '-':
					result = a - b;
					break;
				case '*':
					result = a * b;
					break;
				case '/':
					result = a / b;
					break;
				}
				s.Push(result);
				cout << "结果" << result << "成功入栈" << endl;
			}
			if (!sl.Empty() && sl.Top() == '(') {
				char temp;
				sl.Pop(temp);
				cout << "左括号成功出栈" << endl;
			}
		}
		else{
			char op = x[i];
			while(!sl.Empty() && priority(sl.Top()) >= priority(op)) {
				char h;
				sl.Pop(h);
				double a,b;
				s.Pop(b);
				s.Pop(a);
				double result;
				switch (h) {
				case '+':
					result = a + b;
					break;
				case '-':
					result = a - b;
					break;
				case '*':
					result = a * b;
					break;
				case '/':
					result = a / b;
					break;
				}
				s.Push(result);
				cout << "结果" << result << "成功入栈" << endl;
			}
			sl.Push(op);
			cout << "运算符" << op << "成功入栈" << endl;
		}
	}
	while (!sl.Empty()) {
		double a, b;
		char h;
		sl.Pop(h);
		s.Pop(b);
		s.Pop(a);
		double result;
		switch (h) {
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			result = a / b;
			break;
		}
		s.Push(result);
	}
	double finalresult;
	s.Pop(finalresult);
	cout << "最终结果为：" << finalresult << endl;
	return 0;
}