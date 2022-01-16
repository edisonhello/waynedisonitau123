#include <bits/stdc++.h>
using namespace std;

int v[155], t[155];
int64_t dp[105][105][5204];

const int Z = 2600;


int main() {
	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> v[i] >> t[i];
	}

	memset(dp, 0xc0, sizeof(dp));

	auto update = [&](int64_t &x, int64_t v) {
		x = max(x, v);
	};

	dp[0][0][Z] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			for (int sum = 0; sum <= 5200; ++sum) {
				int64_t vv = dp[i][j][sum];
				update(dp[i + 1][j][sum], vv);
				if (sum + t[i + 1] <= 5200) update(dp[i + 1][j][sum + t[i + 1]], vv + v[i + 1]);
				if (sum - t[i + 1] >= 0) update(dp[i + 1][j][sum - t[i + 1]], vv + v[i + 1]);
				if (sum + t[i + 1] * 2 <= 5200) update(dp[i + 1][j + 1][sum + t[i + 1] * 2], vv + v[i + 1]);
				if (sum - t[i + 1] * 2 >= 0) update(dp[i + 1][j + 1][sum - t[i + 1] * 2], vv + v[i + 1]);
			}
		}
	}

	int64_t mx = LLONG_MIN;
	for (int j = 0; j <= k; ++j) {
		mx = max(mx, dp[n][j][Z]);
	}

	cout << mx << endl;
}

