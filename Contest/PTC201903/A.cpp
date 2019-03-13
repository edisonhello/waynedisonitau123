#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5, maxw = 10000 + 5;
const int inf = 1e9 + 1;
int v[maxn], w[maxn], sz[maxn], has[maxn];
int dp[maxn][maxw];
vector<int> g[maxn];

void dfs(int x, int p, int z) {
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        for (int j = 0; j <= z; ++j) dp[u][j] = dp[x][j];
        dfs(u, x, z - w[u]);
        if (sz[u] == 0) {
            for (int j = w[u]; j <= z; ++j) dp[x][j] = max(dp[x][j], max(0, dp[u][j - w[u]]) + v[u]);
        } else {
            for (int j = w[u]; j <= z; ++j) dp[x][j] = dp[u][j - w[u]] + v[u];
            if (has[u] == sz[u]) {
                dp[x][w[u]] = max(dp[x][w[u]], v[u]);
            }
        }
        sz[x] += sz[u];
    }
    // for (int i = 0; i <= z; ++i) printf("dp[%d][%d] = %d\n", x, i, dp[x][i]);
}

int main() {
    int l, r; 
    while (scanf("%d", &l) != EOF) {
        if (l == -1) break;
        scanf("%d", &r);
        int n; scanf("%d", &n);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= r; ++j)
                dp[i][j] = -1e9;
        }
        for (int i = 0; i <= n; ++i) g[i].clear();
        for (int i = 0; i <= n; ++i) v[i] = w[i] = 0;
        for (int i = 0; i < n; ++i) {
            int j; scanf("%d", &j); --j;
            // printf("j = %d\n", j);
            scanf("%d%d", &v[j], &w[j]);
        }
        int m; scanf("%d", &m);
        assert(m == n - 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int s; scanf("%d", &s);
        for (int i = 0; i <= n; ++i) sz[i] = 0, has[i] = 0;
        for (int i = 0; i < s; ++i) {
            int x; scanf("%d", &x); --x;
            sz[x] = 1;
            has[x] = 1;
        }
        int k = 0;
        while (k < n && sz[k] == 0) ++k;
        if (k == n) k = 0;
        // printf("k = %d\n", k);
        g[n].push_back(k);
        g[k].push_back(n);
        dfs(n, -1, r);
        int _; scanf("%d", &_);
        int ans = -inf;
        for (int i = l; i <= r; ++i) ans = max(ans, dp[n][i] / i);
        /* for (int i = 0; i < n; ++i) {
            if (sz[i] < s) continue;
            for (int j = max(l, 1); j <= r; ++j) 
                ans = max(ans, dp[i][j] / j);
        } */
        if (ans < 0) ans = -1;
        printf("%d\n", ans);
    }
}
