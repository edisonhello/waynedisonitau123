#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw(int b, int n) {
	int a = 1;
	while (n) {
		if (n & 1) a = 1ll * a * b % mod;
		b = 1ll * b * b % mod; n >>= 1;
	}
	return a;
}

int main() {
	string s; cin >> s;
	int x = 0;
	for (char c : s) x = (x * 10ll + (c - '0')) % mod;

	int n; cin >> n;
	while (n--) {
		char c; cin >> c;
		if (c == '+') {
			char z; cin >> z;
			s += z;
			x = (x * 10ll + (z - '0')) % mod;
		} else {
			int y = s.back() - '0';
			s.pop_back();

			x = (((x - y) * 1ll * pw(10, mod - 2)) % mod + mod) % mod;
		}
		cout << x << '\n';
	}
}
