#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t; while (t--) {
		int n; cin >> n;
		if (n <= 5) {
			cout << -1 << '\n';
			continue;
		}
		if (n & 1) {
			cout << 3 << ' ' << n - 3 << '\n';
			continue;
		} else {
			cout << 2 << ' ' << n - 2 << '\n';
		}
	}
}

