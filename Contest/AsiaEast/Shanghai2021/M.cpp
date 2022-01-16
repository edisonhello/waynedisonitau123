#include <bits/stdc++.h>
using namespace std;


int main() {
	int n; cin >> n;
	int k = n / 2;

	cout << fixed << setprecision(9);
	
	if (n % 2 == 0) {
		cout << (double)1 / (2 * k * k * (k + 1)) << endl;
	} else {
		cout << (double)1 / ((k + 1) * (k + 1) * (2 * k + 1)) << endl;
	}
}

