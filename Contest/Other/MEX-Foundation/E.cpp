#include <bits/stdc++.h>
using namespace std;

const int kN = 18;
const int kS = 100 + 5;
const int kInf = 1'000'000'000;
int ed[kN][kN], val[1 << kN];
int dp[kS][1 << kN], best[kS][1 << kN], from[kS][1 << kN];

int main() {
    int n, m, s; scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        u--, v--;
        ed[u][v]++;
        ed[v][u]++;
    }
    if (s == 0) {
        for (int i = 0; i < n; ++i) printf("0 ");
        puts("");
        return 0;
    }
    for (int x = 0; x < (1 << n); ++x) {
        for (int i = 0; i < n; ++i) {
            if ((x >> i & 1) == 0) continue;
            for (int j = i + 1; j < n; ++j) {
                if ((x >> j & 1) == 0) continue;
                val[x] += ed[i][j];
            }
        }
    }
    for (int i = 0; i < (1 << n); ++i) {
        dp[0][i] = -kInf;
        best[0][i] = (1 << n) - 1;
    }
    dp[0][(1 << n) - 1] = 0;
    for (int i = 1; i <= s; ++i) {
        dp[i][0] = -kInf;
        for (int j = 1; j < (1 << n); ++j) {
            int pc = __builtin_popcount(j);
            if (i < pc) {
                dp[i][j] = -kInf;
            } else {
                int b = best[i - pc][j];
                dp[i][j] = dp[i - pc][b] + val[j];
                from[i][j] = b;
            }
        }
        for (int j = 0; j < (1 << n); ++j) best[i][j] = j;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < (1 << n); ++k) {
                if ((k >> j & 1) == 0) {
                    int d = dp[i][best[i][k ^ (1 << j)]];
                    if (d > dp[i][best[i][k]]) best[i][k] = best[i][k ^ (1 << j)];
                }
            }
        }
    }
    int ans = -1, f = -1;
    for (int i = 0; i < (1 << n); ++i) {
        if (dp[s][i] > ans) {
            ans = dp[s][i];
            f = i;
        }
    }
    vector<int> res(n);
    while (s > 0) {
        assert(f > 0);
        for (int i = 0; i < n; ++i) {
            if (f >> i & 1) res[i]++;
        }
        int b = from[s][f];
        assert((b & f) == f);
        s -= __builtin_popcount(f);
        f = b; 
    }
    for (int i = 0; i < n; ++i) printf("%d ", res[i]);
    puts("");
    return 0;
}

