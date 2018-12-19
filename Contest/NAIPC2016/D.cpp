#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000 + 5;
vector<int> g[maxn];
int p[maxn], s[maxn];
double v[maxn];
double dp[maxn][maxn];
int k, n, sz[maxn];

void dfs(int x, int p) {
    sz[x] = 1;
    for (int i = 0; i <= n; ++i) dp[x][i] = -1e9;
    dp[x][0] = 0.0;
    for (const int &u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        vector<double> nxt(sz[x] + sz[u] + 1, -1e9);
        for (int i = 0; i <= sz[x]; ++i) nxt[i] = dp[x][i];
        for (int i = 0; i <= sz[u]; ++i) nxt[i] = max(nxt[i], dp[u][i]);
        for (int i = 0; i <= sz[x]; ++i) {
            for (int j = 0; j <= sz[u]; ++j) {
                nxt[i + j] = max(nxt[i + j], dp[x][i] + dp[u][j]);
            }
        }
        sz[x] += sz[u];
        for (int i = 0; i <= sz[x]; ++i) dp[x][i] = nxt[i];
    }
    for (int i = sz[x] - 1; i >= 0; --i) dp[x][i + 1] = dp[x][i] + v[x];
    dp[x][0] = 0.0;
}

bool check(double x) {
    for (int i = 0; i < n; ++i) v[i] = p[i] - x * s[i];
    dfs(0, -1);
    return dp[0][k + 1] >= 0.0;
}

int main() {
    scanf("%d%d", &k, &n);
    n += 1;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &s[i], &p[i]);
        int f; scanf("%d", &f);
        g[f].push_back(i);
    }
    double l = 0.0, r = 20000;
    for (int it = 0; it < 50; ++it) {
        double m = 0.5 * (l + r);
        if (check(m)) l = m;
        else r = m;
    }
    printf("%.3lf\n", l);
    return 0;
}
