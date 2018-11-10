#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000 + 5;
const int maxk = 1e6 + 5;
const int inf = 1e9;
const long long linf = 1e15;
long long dp[maxn][maxn][2];
int a[maxk], x[maxk];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int p, n, m; scanf("%d%d%d", &p, &m, &n);
        for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
        for (int i = 1; i <= n - 1; ++i) scanf("%d", &x[i]);
        sort(x + 1, x + n);
        sort(a, a + m);
        x[n] = 0;
        x[0] = 0;
        function<int(int)> cost = [&](int x) {
            int z = lower_bound(a, a + m, x) - a;
            int res = inf;
            for (int i = -2; i <= 2; ++i) {
                if (z + i >= 0 && z + i < m) res = min(res, abs(a[z + i] - x));
            }
            return res;
        };
        for (int i = 0; i <= n + 1; ++i) {
            for (int j = 0; j <= n + 1; ++j) {
                dp[i][j][0] = linf;
                dp[i][j][1] = linf;
            }
        }
        dp[1][n][0] = cost(x[1]);
        dp[1][0][1] = cost(x[1]);
        for (int i = 1; i < n - 1; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (dp[i][j][0] != linf) {
                    int l = x[i], r = x[j];
                    if (i + 1 == n - 1) {
                        dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][0] + cost(x[i + 1] - l) + cost(p - r - x[i + 1]));
                        dp[i + 1][i][1] = min(dp[i + 1][i][1], dp[i][j][0] + cost(x[i + 1] - r) + cost(p - l - x[i + 1]));
                    } else {
                        dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][0] + cost(x[i + 1] - l));
                        dp[i + 1][i][1] = min(dp[i + 1][i][1], dp[i][j][0] + cost(x[i + 1] - r));
                    }
                    // printf("dp[%d][%d][0] = %lld\n", i, j, dp[i][j][0]);
                }
                if (dp[i][j][1] != linf) {
                    int l = x[j], r = x[i];
                    if (i + 1 == n - 1) {
                        dp[i + 1][j][1] = min(dp[i + 1][j][1], dp[i][j][1] + cost(x[i + 1] - r) + cost(p - l - x[i + 1]));
                        dp[i + 1][i][0] = min(dp[i + 1][i][0], dp[i][j][1] + cost(x[i + 1] - l) + cost(p - r - x[i + 1]));
                    } else {
                        dp[i + 1][j][1] = min(dp[i + 1][j][1], dp[i][j][1] + cost(x[i + 1] - r));
                        dp[i + 1][i][0] = min(dp[i + 1][i][0], dp[i][j][1] + cost(x[i + 1] - l));
                    }
                    // printf("dp[%d][%d][1] = %lld\n", i, j, dp[i][j][1]);
                }
            }
        }
        long long ans = linf;
        for (int i = 0; i <= n; ++i) {
            ans = min(ans, dp[n - 1][i][0]);
            ans = min(ans, dp[n - 1][i][1]);
        }
        printf("%lld\n", ans);
    }
}
