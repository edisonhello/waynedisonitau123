#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const long long inf = 1e15;
vector<int> g[maxn];
long long dp[maxn][maxn];
bool v[maxn][maxn];
int p[maxn], t[maxn], w;

long long dfs(int x, int k) {
    if (v[x][k]) return dp[x][k];
    if (x == 1 && k == t[x]) return p[x]; 
    dp[x][k] = inf;
    if (k - t[x] >= 0) dp[x][k] = min(dp[x][k], dfs(x, k - t[x]) + p[x]);
    for (int u : g[x]) {
        if (k - t[x] - w < 0) continue;
        long long d = dfs(u, k - t[x] - w);
        if (d + p[x] < dp[x][k]) {
            dp[x][k] = d + p[x];
        }
    }
    v[x][k] = true;
    return dp[x][k];
}

int main() {
    int x; scanf("%d", &x);
    int n, m; scanf("%d %d %d", &n, &m, &w);
    while (m--) {
        int a, b; scanf("%d %d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) scanf("%d %d", &t[i], &p[i]);
    long long ans = dfs(1, x);
    if (ans >= inf) {
        puts("It is a trap.");
        return 0;
    }
    printf("%lld\n", ans);
    return 0;
}
