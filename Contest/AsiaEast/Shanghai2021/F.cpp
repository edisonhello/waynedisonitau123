#include <bits/stdc++.h>
using namespace std;

int cnt[10000007];
int s[10000007];

const int mod = 998244353;

int pw(int b, int n) {
	int a = 1;
	while (n) {
		if (n & 1) a = 1ll * a * b % mod;
		b = 1ll * b * b % mod;
		n >>= 1;
	}
	return a;
}

int inv(int x) {
	return pw(x, mod - 2);
}

int solve() {
	int n, a, A, B, C, m;
	cin >> n >> a >> A >> B >> C >> m;

	for (int i = 1; i <= m; ++i) cnt[i] = 0, s[i] = 0;

	for (int i = 1; i <= n; ++i) {
		a = (1ll * a * a % m * A % m + 1ll * a * B % m + C) % m + 1;
		++cnt[a];
		// cerr << "a = " << a << endl;
	}

	int nn = 0;
	for (int i = 1; i <= m; ++i) {
		s[i] = s[i - 1];
		if (cnt[i]) {
			++nn;
			s[nn] = s[nn - 1];
			if (cnt[i] >= 2) s[nn]++;
		}
	}

	// cerr << "nn = " << nn << endl;
	// for (int i = 1; i <= nn; ++i) {
	// 	cerr << s[i] << ' ';
	// }
	// cerr << endl;

	vector<int> q;
	q.push_back(0);
	int mu = -1000000000, md = 1;
	for (int i = 1; i <= nn; ++i) {
		int tu = -1000000000, td = 1;
		for (int j = q.size() - 1; j >= 0; --j) {
			int jj = q[j];
			int nu = s[i] - s[jj] - 2;
			int nd = i - jj;

			// cerr << i << " to " << jj << " u d " << nu << ' ' << nd << endl;

			if (1ll * nu * td > 1ll * tu * nd) {
				tu = nu;
				td = nd;
			} else break;
		}

		// cerr << "mx t u d " << tu << ' ' << td << endl;

		if (tu * md > mu * td) {
			mu = tu;
			md = td;
		}

		int lu = s[i] - s[q.back()];
		int ld = i - q.back();
		while (q.size() > 1u) {
			int jj = q[q.size() - 2];
			int nu = s[i] - s[jj];
			int nd = i - jj;

			if (1ll * nu * ld >= 1ll * lu * nd) {
				// cerr << "pop " << q.back() << endl;
				q.pop_back();
				lu = nu;
				ld = nd;
			} else break;
		}
	
		q.push_back(i);
	}

	// cerr << "mx u d " << mu << ' ' << md << endl;
	int val = (mu + mod) * 1ll * inv(md) % mod;
	// cerr << "val = " << val << endl;

	val += 2;
	val %= mod;

	// cerr << "add 2 " << val << endl;

	return inv(val);
}

int main() {
	int t; cin >> t; while (t--) {
		cout << solve() << '\n';
	}
}

