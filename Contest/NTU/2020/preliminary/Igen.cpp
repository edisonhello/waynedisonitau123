#include <bits/stdc++.h>
using namespace std;


int main() {
	int n = 2400;
	cout << n << endl;
	for (int i = 0; i < n; ++i) {
		cout << rand() % 1000000000 << ' ' << rand() % 1000000000 << '\n';
	}
}
