#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 5;
int dp[maxn][maxn];

int main() {
	int n, p; scanf("%d%d", &n, &p);
	vector<pair<int, int>> v;
	for (int i = 0; i < n; ++i) {
		int l, r; scanf("%d%d", &l, &r);
		v.emplace_back(l, r);
	}

	int ans = -1e9;

	sort(v.begin(), v.end(), [](pair<int, int> p, pair<int, int> q) {
		return p.first + p.second < q.first + q.second;
	});

	function<int()> solve = [&]() {
		for (int i = 0; i < maxn; ++i) {
			for (int j = 0; j < maxn; ++j)
				dp[i][j] = -1e9;
		}
		dp[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= p; ++j) {
				pair<int, int> inter = v[i - 1];
				for (int k = i - 1; k >= 0; --k) {
					inter.second = min(inter.second, v[k].second);
					inter.first = max(inter.first, v[k].first);
					if (inter.second > inter.first)
						dp[i][j] = max(dp[i][j], dp[k][j - 1] + inter.second - inter.first);
				}
			}
		}
		return dp[n][p];
	};

	ans = max(ans, solve());

	sort(v.begin(), v.end(), [](pair<int, int> p, pair<int, int> q) {
		if (p.second == q.second)
			return p.first < q.first;
		return p.second < q.second;
	});

	ans = max(ans, solve());
	sort(v.begin(), v.end(), [](pair<int, int> p, pair<int, int> q) {
		return p < q;
	});
	ans = max(ans, solve());
	printf("%d\n", ans);
}
