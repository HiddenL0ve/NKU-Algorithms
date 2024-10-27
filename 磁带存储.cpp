#include<iostream>
using namespace std;
int main() {
	int n, L;
	cin >> n >> L;
	int l[1000];
	for (int i = 0; i < n; i++) {
		cin >> l[i];
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (l[j] > l[j + 1]) {
				int tem = l[j];
				l[j] = l[j + 1];
				l[j + 1] = tem;
			}
		}
	}
	int curlen = 0;
	int count = 0;
	for (int i = 0; i < n; i++) {
		curlen += l[i];
		if (curlen > L) {
			break;
		}
		count++;
	}
	cout << count << endl;
	return 0;
}