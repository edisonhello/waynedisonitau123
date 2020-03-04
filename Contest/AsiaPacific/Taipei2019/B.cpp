#include <bits/stdc++.h>
using namespace std;

const int kN = 100'000 + 5;
const int kInf = 1e9;
set<int> g[kN];
int dp[kN][3];
int deled[kN];
// dp[x][0] = not taken care
// dp[x][1] = taken care but not marked
// dp[x][2] = marked

void Dfs(int x, int p) {
    int sum = 0;
    dp[x][0] = 0;
    for (int u : g[x]) {
        if (u == p) continue;
        Dfs(u, x);
        sum += min(dp[u][2], dp[u][1]);
        dp[x][0] += min(dp[u][1], dp[u][2]);
        dp[x][2] += min(dp[u][0], min(dp[u][1], dp[u][2]));
    }
    dp[x][2]++;
    dp[x][1] = kInf;
    int ch = 0;
    for (int u : g[x]) {
        if (u == p) continue;
        ch += 1;
        int tsum = sum - min(dp[u][1], dp[u][2]);
        dp[x][1] = min(dp[x][1], tsum + dp[u][2]);
    }
    // printf("dp[%d][0] = %d\n", x, dp[x][0]);
    // printf("dp[%d][1] = %d\n", x, dp[x][1]);
    // printf("dp[%d][2] = %d\n", x, dp[x][2]);
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
    if (root >= n) {
        puts("1");
        exit(0);
    }
    Dfs(root, -1);
    printf("%d\n", min(dp[root][1], dp[root][2]));
    return 0;
}
