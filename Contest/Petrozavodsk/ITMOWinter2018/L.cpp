#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

const int mod = 1000000007;

int pw(int b, long long n, int m, int a = 1) {
	while (n) {
		if (n & 1) a = 1ll * a * b % m;
		b = 1ll * b * b % m;
		n >>= 1;
	}
	return a;
}

int main() {
	cc_hash_table<int, int> mp;
	cc_hash_table<int, int> rev;
	int a = 1, i = 1;
	mp[a] = 1;
	rev[1] = a;

	int fi = -1, si = -1;
	for (int i = 2; ; ++i) {
		a = (a - 1ll * a * a % mod * 250000002 % mod + mod) % mod;
		auto it = mp.find(a);
		if (it != mp.end()) {
			fi = it->second;
			si = i - it->second;
			// cerr << "i a prev = " << i << ' ' << a << ' ' << it->second << endl;
			// cout << "i a " << i << ' ' << a << endl;

			break;
		}
		mp[a] = i;
		rev[i] = a;
		// cerr << "i a " << i << ' ' << a << endl;
		// if ((i & ((1 << 24) - 1)) == 0) cerr << "i = " << i << endl;

	}

	auto GetA = [&] (long long x) {
		if (x <= fi) return rev[x];
		return rev[(x - fi) % si + fi];
	};

	long long n; cin >> n;
	int p = 1ll * pw(2, pw(2, n, mod - 1) - 2 + mod - 1, mod);
	int q = p;
	p = 1ll * p * GetA(n) % mod;
	cout << p << ' ' << q << endl;
}

