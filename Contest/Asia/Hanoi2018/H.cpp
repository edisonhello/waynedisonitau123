#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
int dp[maxn * maxn];
vector<int> g[maxn * maxn];

/* int dfs(int h, int t) {
    if (dp[h][t] != -1) return dp[h][t];
    if (h == 0 && t == 0) return 0;
    dp[h][t] = 1e9;
    if (h >= 2) dp[h][t] = min(dp[h][t], dfs(h - 2, t) + 1);
    if (t >= 2) dp[h][t] = min(dp[h][t], dfs(h + 1, t - 2) + 1);
    // if (t >= 1) dp[h][t] = min(dp[h][t], dfs(h, t + 1) + 1);
    return dp[h][t];
} */

int main() {
    int h, t;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) {
            if (j >= 1 && j + 1 < maxn) {
                g[i * maxn + j + 1].push_back(i * maxn + j);
            }
            if (j >= 2 && i + 1 < maxn) {
                g[i * maxn + j].push_back((i + 1) * maxn + j - 2);
                g[(i + 1) * maxn + j - 2].push_back(i * maxn + j);
            }
            if (i >= 2) {
                // g[i * maxn + j].push_back((i - 1) * maxn + j);
                g[(i - 2) * maxn + j].push_back(i * maxn + j);
            }
        }
    }
    queue<int> q;
    q.push(0);
    dp[0] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int u : g[x]) {
            if (dp[u] == -1) {
                dp[u] = dp[x] + 1;
                q.push(u);
            } 
        }
    }
    while (cin >> h >> t) {
        if (h == 0 && t == 0) break;
        cout << dp[h * maxn + t] << endl;
    }
}
