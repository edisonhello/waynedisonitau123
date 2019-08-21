#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
vector<pair<int, int>> g[maxn];
long long dp[maxn][101];
long long tmp[maxn];
int sz[maxn];

void dfs(int x, int p, int k) {
    sz[x] = 0;
    int ch = 0;
    for (int i = 0; i <= k; ++i) dp[x][i] = 1e18;
    dp[x][0] = 0;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first;
        int w = g[x][i].second;
        if (u == p) continue;

        ++ch;
        dfs(u, x, k);
        for (int i = 0; i <= min(sz[x] + sz[u], k); ++i) tmp[i] = 1e18;
        for (int i = 0; i <= sz[x]; ++i) {
            for (int j = 0; j <= sz[u] && i + j <= k; ++j)
                tmp[i + j] = min(tmp[i + j], dp[x][i] + dp[u][j] + w * 1ll * j * (k - j));
        }
        sz[x] += sz[u];
        sz[x] = min(sz[x], k);
        for (int i = 0; i <= sz[x]; ++i) dp[x][i] = min(dp[x][i], tmp[i]);
    }
    if (ch == 0) {
        sz[x] = 1;
        dp[x][1] = 0;
    }
    // for (int i = 0; i <= k; ++i)
    //    printf("dp[%d][%d] = %lld\n", x, i, dp[x][i]);
}

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n, k; scanf("%d%d", &n, &k);
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n - 1; ++i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            --u, --v;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        printf("Case #%d: ", tc);
        if (n == 2) {
            if (k == 1) printf("0\n");
            else printf("%d\n", g[0][0].second);
            continue;
        }
        int root = 0;
        while ((int)g[root].size() == 1) ++root;
        dfs(root, -1, k);
        long long ans = 1e18;
        for (int i = 0; i < n; ++i) ans = min(ans, dp[i][k]);
        printf("%lld\n", ans);
    }
}
