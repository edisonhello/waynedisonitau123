#include <bits/stdc++.h>
using namespace std;

const int maxn = 15;
int w[maxn], h[maxn], q[maxn];
long long cost[1 << maxn];
long long dp[1 << maxn][maxn + 1];
bool v[1 << maxn][maxn + 1];

long long dfs(int s, int k) {
    if (s == 0 && k == 0) return 0;
    if (k == 0) return 1e18;
    if (v[s][k]) return dp[s][k];
    dp[s][k] = 1e18;
    for (int sub = s; sub; sub = (sub - 1) & s) {
        dp[s][k] = min(dp[s][k], dfs(s ^ sub, k - 1) + cost[sub]);
    }
    v[s][k] = true;
    return dp[s][k];
}

int main() {
    int n, k; cin >> n >> k;
    if (k >= n) exit((puts("0"), 0));
    for (int i = 0; i < n; ++i) cin >> w[i] >> h[i] >> q[i];
    for (int i = 0; i < (1 << n); ++i) {
        int mw = 0, mh = 0;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                mw = max(mw, w[j]);
                mh = max(mh, h[j]);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                cost[i] += (mw * mh - w[j] * h[j]) * 1ll * q[j];
            }
        }
    }
    printf("%lld\n", dfs((1 << n) - 1, k));
}
