#include <iostream>
using namespace std;
int main() {
	long long a[100];
	int n;
	cin>>n;
	for (int i = 0; i < n; i++) {
		cin>>a[i];
	}
	int j = 0;
	while (j < n) {
		if (j < n-1) {
			cout << "(" << a[j];
			j++;
		}
		else if (j==n-1){
			break;
		}
		if (j < n && a[j] < a[j - 1]) {
			while (j < n && a[j] < a[j - 1]) {
				cout << "," << a[j];
				j++;
			}
			cout << ")";
			if (j<n){
				cout << ",";
			}
			if (j != 0) {
				j--;
			}
		}
		else if (j<n && a[j]>a[j - 1]) {
			while (j<n && a[j]>a[j - 1]) {
				cout << "," << a[j];
				j++;
			}
			cout << ")";
			if (j < n) {
				cout << ",";
			}
			if (j != 0) {
				j--;
			}
		
		}
	}
	cout << "¡£";
	return 0;
}
