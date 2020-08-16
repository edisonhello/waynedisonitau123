#include <bits/stdc++.h>
using namespace std;

int main() {
	int t = 1; cout << t << endl;
	while (t--) {
		long long n = 1ll * rand() * rand() % 1000000000'000000000;
		int r = 5000;
		cout << n << ' ' << r << endl;
		while (r--) {
			long long i = 1ll * rand() * rand() % (n - 1) + 1;
			cout << i << ' ' << rand() % 10 << endl;
		}
	}
}
