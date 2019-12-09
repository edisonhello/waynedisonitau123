#include <bits/stdc++.h>
using namespace std;

const int kN = 200'000 + 5;
const long long kInf = 1'000'000'000'000'000;
vector<pair<int, int>> g[kN];
long long dp[kN][3];
int c[kN];

void Dfs(int x, int p) {
    for (auto &e : g[x]) {
        int u = e.first, w = e.second;
        if (u == p) continue;
        Dfs(u, x);
        dp[x][0] += min(min(dp[u][0], dp[u][2]), dp[u][1] + w);
        dp[x][1] += min(min(dp[u][1], dp[u][2]), dp[u][0] + w);
        dp[x][2] += min(dp[u][2], min(dp[u][0], dp[u][1]) + w);
    }
    if (c[x] != -1) {
        dp[x][c[x] ^ 1] = kInf;
        dp[x][2] = kInf;
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    memset(c, -1, sizeof(c));
    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int x; scanf("%d", &x); --x;
        c[x] = 0;
    }
    int k; scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        int x; scanf("%d", &x); --x;
        c[x] = 1;
    }
    Dfs(0, -1);
    printf("%lld\n", min(min(dp[0][0], dp[0][1]), dp[0][2]));
    return 0;
}
