#include <bits/stdc++.h>
using namespace std;

const int kN = 20;
const int kInf = 1'000'000'000;
vector<pair<int, int>> g[kN];
int w[kN][kN];

struct Route {
    int dp[1 << kN][kN], st, n;
    bool v[1 << kN][kN];

    Route(int s, int n) : st(s), n(n) {}

    int Dfs(int s, int x) {
        if (v[s][x]) return dp[s][x];
        if (s == (1 << x)) return w[st][x];
        int t = s ^ (1 << x);
        dp[s][x] = kInf;
        for (int i = 0; i < n; ++i) {
            if (t >> i & 1) dp[s][x] = min(dp[s][x], Dfs(t, i) + w[x][i]);
        }
        v[s][x] = true;
        return dp[s][x];
    }
};

int main() {
    int n, m, tc = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) w[i][j] = 0;
                else w[i][j] = kInf;
            }
        }
        for (int i = 0; i < m; ++i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            ::w[u][v] = min(::w[u][v], w);
            ::w[v][u] = min(::w[u][v], w);
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j)
                    w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
            }
        }
        if (n == 3) {
            printf("Case %d: %d\n", ++tc, 2 * (w[0][1] + w[1][2]));
            continue;
        }
        Route r1(0, n), r2(n - 1, n);
        int h = n - 2, ans = kInf, mask = 0;
        for (int i = 1; i < n - 1; ++i) mask |= (1 << i);
        for (int s = 0; s < (1 << n); ++s) {
            if ((s & 1) || (s >> (n - 1) & 1)) continue;
            if (__builtin_popcount(s) == h / 2) {
                int go = kInf, ba = kInf;
                int t = mask ^ s;
                for (int x = 0; x < n; ++x) {
                    if ((s >> x & 1) == 0) continue;
                    for (int y = 0; y < n; ++y) {
                        if ((mask >> y & 1) == 0) continue;
                        go = min(go, r1.Dfs(s, x) + r2.Dfs(t, y) + w[x][y]);
                        ba = min(ba, r2.Dfs(s, x) + r1.Dfs(t, y) + w[x][y]);
                    }
                }
                ans = min(ans, go + ba);
            }
        }
        printf("Case %d: %d\n", ++tc, ans);
    }
}

