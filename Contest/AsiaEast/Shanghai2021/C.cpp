#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, M;
	cin >> N >> M;
	vector<string> grid(N);
	for (int i = 0; i < N; ++i) {
		cin >> grid[i];
	}
	vector<vector<int>> adj(N, vector<int>(M));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			int k = j;
			while (k >= 0 && (grid[i][k] == '0' || grid[i][k] == '2')) {
				adj[i][j] |= (1 << k);
				k--;
			}
			k = j;
			while (k < M && (grid[i][k] == '0' || grid[i][k] == '2')) {
				adj[i][j] |= (1 << k);
				k++;
			}
		}
	}
	vector<vector<int>> dp(1 << M, vector<int>(1 << M, N * M + 1));
	dp[0][0] = 0;
	for (int i = 0; i < N; ++i) {
		vector<vector<int>> nxt(1 << M, vector<int>(1 << M, N * M + 1));
		for (int s = 0; s < (1 << M); ++s) {
			for (int t = 0; t < (1 << M); ++t) {
				if (dp[s][t] == N * M + 1) {
					continue;
				}
				assert(dp[s][t] >= __builtin_popcount(t));
				for (int x = 0; x < (1 << M); ++x) {
					int need = 0;
					int nt = t;
					for (int j = 0; j < M; ++j) {
						if (grid[i][j] == '1' && (nt >> j & 1)) nt ^= (1 << j);
					}
					for (int j = 0; j < M; ++j) {
						if (grid[i][j] == '0' && ((nt | x) >> j & 1) == 0 && (adj[i][j] & x) == 0) need |= (1 << j);
					}
					bool ok = true;
					for (int j = 0; j < M; ++j) {
						if ((s >> j & 1) && grid[i][j] == '1') ok = false;
					}
					if (ok) {
						int mask = (s | need) & ~x;
						nxt[mask][x | nt] = min(nxt[mask][x | nt], dp[s][t] + __builtin_popcount(x));
					}
				}
			}
		}
		dp.swap(nxt);
	}
	int ans = N * M + 1;
	for (int i = 0; i < (1 << M); ++i) {
		ans = min(ans, dp[0][i]);
	}
	cout << ans << "\n";
	return 0;
}

