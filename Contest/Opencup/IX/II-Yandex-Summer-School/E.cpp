#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int adj[maxn];
int dp[2][1 << maxn], n, m;


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        adj[u] |= (1 << v);
        adj[v] |= (1 << u);
    }

    for (int i = 0; i < (1 << n); ++i) dp[1][i] = 1e9;
    dp[1][0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int s = 0; s < (1 << n); ++s) dp[i & 1][s] = 1e9;
        for (int s = 0; s < (1 << n); ++s) {
            dp[i & 1][s] = min(dp[i & 1][s], dp[i & 1 ^ 1][s]);
            for (int j = 0; j < i; ++j) {
                if (s >> i & 1) continue;
                if (s >> j & 1) continue;
                if ((adj[i] >> j & 1) == 0) continue;
                int cost = 4 - 1 - __builtin_popcount((adj[i] ^ s) & adj[i]) - __builtin_popcount((adj[j] ^ s) & adj[j]);
                dp[i & 1][s ^ (1 << j) ^ (1 << i)] = min(dp[i & 1][s ^ (1 << i) ^ (1 << j)], dp[i & 1 ^ 1][s] + cost);
            } 
        }
    }

    int ans = m;
    for (int i = 0; i < (1 << n); ++i) ans = min(ans, dp[(n - 1) & 1][i] + m);
    printf("%d\n", ans);
    return 0;
}
