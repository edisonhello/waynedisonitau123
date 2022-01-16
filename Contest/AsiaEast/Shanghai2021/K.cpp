#include <bits/stdc++.h>
using namespace std;


int main() {
	int n;
	cin >> n;
	if (n == 3) {
		cout << "Unlucky" << endl;
		exit(0);
	}

	if (n % 2 == 0) {
		for (int i = 0; i < n; i += 2) {
			if (i % 4 == 0) {
				cout << "10";
			}
			else {
				cout << "01";
			}
		}
	} else {
		cout << "100";
		n -= 3;
		for (int i = 0; i < n; i += 2) {
			if (i % 4 == 0) {
				cout << "01";
			}
			else {
				cout << "10";
			}
		}
	}
	cout << endl;
}

