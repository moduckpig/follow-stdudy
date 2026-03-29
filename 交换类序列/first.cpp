#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;
vector <long long> readdata() {
	vector <long long> data;
	ifstream read("./data.txt");
	if (!read.is_open()) {
		cerr << "无法打开文件!";
		return data;
	}
	long long n;
	while (read >> n) {
		data.push_back(n);
	}
	read.close();
	return data;
}
vector <long long>randomselect(const vector<long long>& data, int count) {
	vector <long long>result;
	if (data.empty() || count <= 0) {
		return result;
	}
	count = min(count, (int)data.size());
	default_random_engine rng(time(0));
	uniform_int_distribution<int> dist(0, data.size() - 1);
	for (int i = 0; i < count; i++) {
		int randomidx = dist(rng);
		result.push_back(data[randomidx]);
	}
	return result;
}
void stockdata(const vector<long long>& selecteddata) {
	ofstream write("result.txt");
	if (!write.is_open()) {
		cerr << "无法打开文件";
		return;
	}
	for (long long n : selecteddata) {
		write << n<< endl;
	}
	write.close();
}
void arrange1(vector<long long>& a,int n) {//标准冒泡排序；
	for (int i = n-1; i >0; i--) {//控制冒泡次数；
		for (int j = 0; j < i; j++) {
			long long tempt = 0;
			if (a[j] > a[j+1]) {
				tempt = a[j];
				a[j] = a[j+1];
				a[j + 1] = tempt;
			}
		}
	}
}
void arrange2(vector<long long >& a, int n) {//设置哨兵冒泡排序；
	for (int i = n - 1; i > 0; i--) {
		bool flag = false;
		for (int j = 0; j < i; j++) {
			long long tempt = 0;
			if (a[j] > a[j + 1]) {
				tempt = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tempt;
				flag = true;
			}
		}
		if (flag == false) {
			break;
		}
	}
}
void arrange3(vector<long long>& a, int n) {//双向冒泡排序；
	if (n <= 1) return;
	int small = 0;
	int big = n - 1;
	bool swapped;
	while (small < big) {
		swapped = false;
		for (int i = small; i < big; i++) {
			if (a[i] > a[i + 1]) {
				long long tempt = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tempt;
				swapped = true;
			}
		}
		big--;
		if (!swapped) break;
		swapped = false;
		for (int i = big; i > small; i--) {
			if (a[i] < a[i - 1]) {
				long long tempt = a[i];
				a[i] = a[i -1];
				a[i - 1] = tempt;
				swapped = true;
			}
		}
		small++;
		if (!swapped) break;
	}
}
void arrange4(int start,int end,long long *a) {
	if (start >= end) {
		return;
	}
	long long tempt = a[start];
	int left = start;
	int right = end;
	while (left < right) {
		while (left < right && a[right]>=tempt) {
			--right;
		}
		a[left] = a[right];
		while (left < right && a[left] <=tempt) {
			++left;
		}
		a[right] = a[left];
	}
	a[left] = tempt;
	arrange4(start, left - 1, a);
	arrange4(left + 1, end, a);
}
void arrange4(vector<long long >& a,int n){
	if (a.empty() || n <= 1) return;
	arrange4(0, n - 1, a.data());
}
void arrange5(vector<long long>& a, int n) {
	if (n <= 1) return;
	int left = 0, right = n - 1;
	bool leftSorted, rightSorted; 
	while (left < right) {
		leftSorted = true;
		long long tempt = 0;
		for (int i = left; i < right; i++) {
			if (a[i] > a[i + 1]) {
				tempt = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tempt;
				leftSorted = false;
			}
		}
		right--;
		if (leftSorted) break;

		rightSorted = true;
		tempt = 0;
		for (int i = right; i > left; i--) {
			if (a[i] < a[i - 1]) {
				tempt = a[i];
				a[i] = a[i -1];
				a[i - 1] = tempt;
				rightSorted = false;
			}
		}
		left++;
		if (rightSorted) break;
	}
}

int main() {
	vector<long long>alldata = readdata();
	if (alldata.empty()) {
		return 1;
	}
	//选择随机抽不啦？？
	/*int min_count = 5;
	int max_count;
	std::cout << "请输入最大抽选个数：" << endl;
	cin >> max_count;
	default_random_engine rng_count(time(0));
	uniform_int_distribution<int>dist_count(min_count,max_count);
	int randomcount = dist_count(rng_count);
	std::cout << "此次抽选的排序个数为："<<randomcount << endl;
	vector <long long>selected = randomselect(alldata,randomcount);*/
	//此处不是随机抽嘟，修改下面的8000就可以选择想抽的数据量
	vector <long long>selected = randomselect(alldata, 70000);
	for (long long num : selected) {
		std::cout << num << " ";
	}
	std::cout << endl;
	vector<long long>arr1 = selected;
	arrange1(arr1, arr1.size());
	for (long long num : arr1) {
		std::cout << num << " ";
	}
	std::cout << endl;
	stockdata(arr1);
	std::cout << "排序结果写入result文件里" <<"way1" << endl;


	vector<long long>arr2 = selected;
	arrange2(arr2, arr2.size());
	for (long long num : arr2) {
		std::cout << num << " ";
	}
	std::cout << endl;
	stockdata(arr2);
	std::cout << "排序结果写入result文件里" <<"way2" << endl;


	vector<long long>arr3 = selected;
	arrange3(arr3, arr3.size());
	for (long long num : arr3) {
		std::cout << num << " ";
	}
	std::cout << endl;
	stockdata(arr3);
	std::cout << "排序结果写入result文件里" <<"way3" << endl;


	vector<long long>arr4= selected;
	arrange4(arr4, arr4.size());
	for (long long num : arr4) {
		std::cout << num << " ";
	}
	std::cout << endl;
	stockdata(arr4);
	std::cout << "排序结果写入result文件里" <<"way4" << endl;
	

	vector<long long>arr5 = selected;
	arrange5(arr5, arr5.size());
	for (long long num : arr5) {
		std::cout << num << " ";
	}
	std::cout << endl;
	stockdata(arr5);
	std::cout << "排序结果写入result文件里" << "way5" << endl;

	return 0;
}
