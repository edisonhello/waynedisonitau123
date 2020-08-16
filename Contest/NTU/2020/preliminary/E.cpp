#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

typedef array<array<int, 10>, 10> mat;

mat up, down, pairr;

mat operator* (const mat &a, const mat &b) {
	mat r;
	for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) r[i][j] = 0;
	for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) for (int k = 0; k < 10; ++k) {
		r[i][j] += 1ll * a[i][k] * b[k][j] % mod;
		if (r[i][j] >= mod) r[i][j] -= mod;
	}
	return r;
}

mat pow(mat b, long long n) {
	mat a;
	for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) a[i][j] = i == j;
	while (n) {
		if (n & 1) a = a * b;
		b = b * b; n >>= 1;
	}
	return a;
}

void print(mat x) {
	cerr << "mat: \n";
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			cerr << x[i][j] << ' ';
		}
		cerr << endl;
	}
}

void solve() {
	mat dp;
	for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) dp[i][j] = i == 0 && j >= 1;

	long long n; int r; cin >> n >> r;
	long long j = 1;

	vector<pair<long long, int>> v;
	for (int i = 0; i < r; ++i) {
		long long j; int x; cin >> j >> x;
		v.emplace_back(j, x);
	}
	sort(v.begin(), v.end());

	for (int i = 1; i < r; ++i) {
		if (v[i].first == v[i - 1].first) {
			if (v[i].second != v[i - 1].second) {
				cout << 0 << '\n';
				return;
			}
		}
	}

	for (int _ = 0; _ < r; ++_) {
		if (_ && v[_].first == v[_ - 1].first) continue;

		auto [i, x] = v[_];

		if (j % 2 == 0 && j < i) {
			dp = dp * down;
			++j;
		}
		long long p = (i - j) / 2;
		dp = dp * pow(pairr, p);
		j += p * 2;
		if (i != j) {
			dp = dp * up;
			++j;
		}

		assert(i == j);

		if (i % 2 == 1) {
			mat ndp;
			for (int x = 0; x < 10; ++x) for (int y = 0; y < 10; ++y) ndp[x][y] = 0;
			for (int i = x; i < 10; ++i) ndp[0][i] = dp[0][i - x];
			dp = ndp;
		} else {
			mat ndp;
			for (int x = 0; x < 10; ++x) for (int y = 0; y < 10; ++y) ndp[x][y] = 0;
			for (int i = 0; i + x < 10; ++i) ndp[0][i] = dp[0][i + x];
			dp = ndp;
		}
		++j;
	}
	{
		long long i = n;
		if (i % 2 == 1 && j % 2 == 0) {
			dp = dp * down;
		}
		// print(dp);
		dp = dp * pow(pairr, (i - j) / 2);
		// print(dp);
		if (i % 2 == 0 && j % 2 == 1) {
			dp = dp * up;
		}
		// print(dp);
		j = i;
	}

	long long sum = 0;
	for (int i = 0; i < 10; ++i) {
		sum += dp[0][i];
	}
	cout << sum % mod << '\n';
}

int main() {
	ios_base::sync_with_stdio(0);
	for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) {
		up[i][j] = i <= j;
		down[i][j] = i >= j;
	}

	pairr = up * down;

	// print(up);
	// print(down);
	// print(pairr);

	int t; cin >> t; while (t--) solve();
}
