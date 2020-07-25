#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m, c;
	cin >> n >> m >> c;
	vector<vector<int>> cnt(n, vector<int>(c));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int x;
			cin >> x;
			cnt[i][x - 1]++;
		}
	}
	constexpr int kMod = 1'000'000'000 + 87;
	constexpr int kIter = 100;

	auto fpow = [&](int a, int n) {
		int res = 1;
		while (n > 0) {
			if (n & 1) res = 1LL * res * a % kMod;
			a = 1LL * a * a % kMod;
			n >>= 1;
		}
		return res;
	};

	const int kA = 1LL * m * fpow(c, kMod - 2) % kMod;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < c; ++j) {
			cnt[i][j] = (cnt[i][j] + kMod - kA) % kMod;
		}
	}
	mt19937 rng(7122);
	uniform_int_distribution<int> dis(0, kMod - 1);
	vector<vector<int>> pvec(n, vector<int>(kIter));
	int res = 0;
	for (int it = 0; it < kIter; ++it) {
		vector<int> vec(c);
		for (int i = 0; i < c; ++i) {
			vec[i] = dis(rng);
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < c; ++j) {
				pvec[i][it] += 1LL * cnt[i][j] * vec[j] % kMod;
				pvec[i][it] >= kMod ? pvec[i][it] -= kMod : 0;
			}	
		}	
	}
	int h = n / 2;
	map<vector<int>, int> dp;
	for (int s = 0; s < (1 << h); ++s) {
		vector<int> sum(kIter, 0);
		for (int i = 0; i < h; ++i) {
			if (s >> i & 1) {
				for (int j = 0; j < kIter; ++j) {
					(sum[j] += pvec[i][j]) >= kMod ? sum[j] -= kMod : 0;
				}
			}
		}
		if (dp.find(sum) == dp.end() || __builtin_popcount(dp[sum]) < __builtin_popcount(s)) {
			dp[sum] = s;
		}
	}
	int nh = n - h;
	for (int s = 0; s < (1 << nh); ++s) {
		vector<int> sum(kIter, 0);
		for (int i = 0; i < nh; ++i) {
			if (s >> i & 1) {
				for (int j = 0; j < kIter; ++j) {
					(sum[j] += pvec[h + i][j]) >= kMod ? sum[j] -= kMod : 0;
				}
			}
		}
		for (int i = 0; i < kIter; ++i) {
			sum[i] = (kMod - sum[i]) % kMod;
		}
		if (dp.find(sum) != dp.end()) {
			res = max(res, __builtin_popcount(s) + __builtin_popcount(dp[sum]));
		}
	}
	cout << res << "\n";
}

