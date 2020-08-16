#include <bits/stdc++.h>
using namespace std;


int main() {
	int n = 150, m = n * (n - 1) / 2;
	cout << n << ' ' << m << endl;
	for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
		cout << i << ' ' << j << ' ' << rand() % 1000000 << '\n';
	}
}
