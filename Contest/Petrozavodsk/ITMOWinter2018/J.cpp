#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

vector<pair<int, int>> dp[100005];
int a[100005];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, h0; cin >> n >> h0;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	dp[1].emplace_back(h0, 1);
	for (int i = 1; i <= n; ++i) {
		// cerr << "dp i = " << i << endl;
		int sum = 0;
		for (auto &p : dp[i]) {
			// cerr << "p = " << p.first << " , " << p.second << endl;
			sum += p.second;
			if (sum >= mod) sum -= mod;

			if (p.first == a[i]) continue;
			if (i + p.first > n) continue;
			dp[i + p.first].emplace_back(p.first, p.second);
		}

		if (i + a[i] <= n) dp[i + a[i]].emplace_back(a[i], sum);

		if (i != n) vector<pair<int, int>>().swap(dp[i]);
	}

	int ans = 0;
	for (auto &p : dp[n]) {
		ans += p.second;
		if (ans >= mod) ans -= mod;
	}

	cout << ans << endl;
}

