#include <iostream>
using namespace std;
class List {
public:
	List(const int m) {
		count = 0;
		maxlen = m;
		data = new int[maxlen];
	};
	~List() {
		delete[] data;
	}
	int Length()const {
		return count;
	};
	bool Get_element(const int i, int& x)const {
		if (i < 0 || i > count) {
			return false;
		}
		x = data[i - 1];
		return true;
	};
	int Locate(int& x) {
		for (int i = 0; i < count; i++) {
			if (data[i] == x) {
				return (i + 1);
			}
		}
		return 0;
	};
	bool Insert(const int i, const int x) {
		if (count == maxlen || i<0 || i>count) {
			return false;
		}
		for (int j = count; j >= i; j--) {
			data[j] = data[j - 1];
		}
		data[i - 1] = x;
		count++;
		return true;
	};
	bool Delete_element(const int i) {
		if (Length() == 0 || i<0 || i>maxlen) {
			return false;
		}
		for (int j = i + 1; j <= count; j++) {
			data[j - 2] = data[j - 1];
		}
		count--;
		return true;
	};
private:
	int count;
	int maxlen;
	int* data;
};