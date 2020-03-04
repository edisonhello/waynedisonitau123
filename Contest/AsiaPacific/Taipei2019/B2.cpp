#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 100'000 + 5;
const int kInf = 1e9;
set<int> g[kN];
long long dp[kN][4];
int deled[kN];

void Dfs(int x, int p) {
    long long sum = 0, sum2 = 0;
    int ch = 0;
    for (int u : g[x]) {
        if (u == p) continue;
        ch += 1;
        Dfs(u, x);
        sum += min(min(dp[u][3], dp[u][0]), dp[u][2]);
        sum2 += min(dp[u][0], dp[u][2]);
        dp[x][0] += min(dp[u][0], dp[u][2]);
        dp[x][2] += min(min(dp[u][0], dp[u][1]), min(dp[u][3], dp[u][2]));
    }
    if (ch == 0) {
        dp[x][2] = 1;
        dp[x][1] = 0;
        dp[x][3] = kInf;
        dp[x][0] = kInf;
        return;
    }
    dp[x][2]++;
    dp[x][1] = dp[x][3] = kInf;
    for (int u : g[x]) {
        if (u == p) continue;
        dp[x][1] = min(dp[x][1], sum - min(min(dp[u][3], dp[u][0]), dp[u][2]) + dp[u][1]);
    }
    for (int u : g[x]) {
        if (u == p) continue;
        dp[x][3] = min(dp[x][3], sum2 - min(dp[u][0], dp[u][2]) + min(dp[u][1], dp[u][3]));
    }
    // fprintf(stderr, "dp[%d][0] = %lld\n", x, dp[x][0]);
    // fprintf(stderr, "dp[%d][1] = %lld\n", x, dp[x][1]);
    // fprintf(stderr, "dp[%d][2] = %lld\n", x, dp[x][2]);
    // fprintf(stderr, "dp[%d][3] = %lld\n", x, dp[x][3]);
}


int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].insert(v);
        g[v].insert(u);
    }
    for (int i = 0; i < n; ++i) {
        if (g[i].size() == 2u) {
            int u = *g[i].begin();
            int v = *next(g[i].begin());
            g[u].erase(i);
            g[v].erase(i);
            g[u].insert(v);
            g[v].insert(u);
            deled[i] = 1;
        }
    }
    int root = 0;
    while (root < n && (deled[root] || g[root].size() < 2u)) ++root;
    int root = 0;
    while (root < n && g[root].size() != 1) ++root;
    if (root >= n) {
        puts("1");
        exit(0);
    }
    // assert(g[root].size() == 1);
    // fprintf(stderr, "root = %d\n", root);
    // int root = 0;
    Dfs(root, -1);
    for (int u : g[root]) {
        printf("%lld\n", min(dp[u][0], dp[u][2]));
    }
    return 0;
    long long ans = min(min(dp[root][0], dp[root][2]), dp[root][3]);
    long long sum = 0;
    for (int u : g[root]) {
        sum += min(min(dp[u][3], dp[u][2]), dp[u][0]);
    }
    for (int u : g[root]) {
        ans = min(ans, min(dp[u][0], dp[u][2]) + sum - min(min(dp[u][3], dp[u][2]), dp[u][0]));
    }
    for (int u : g[root]) {
        for (int v : g[root]) {
            if (u == v) continue;
            long long du = min(min(dp[u][3], dp[u][2]), dp[u][0]);
            long long dv = min(min(dp[v][3], dp[v][2]), dp[v][0]);
            long long tsum = sum - du - dv + min(dp[u][0], dp[u][2]) + dp[v][1];
            ans = min(ans, tsum);
        }
    }
     printf("%lld\n", ans);
    return 0;
}
