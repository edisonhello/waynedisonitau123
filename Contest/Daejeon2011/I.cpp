#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
const long long inf = 1e18;
int p[maxn], e[maxn], tp[maxn], te[maxn];
long long dp[maxn][maxn][maxn][2];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &p[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &e[i]);
        int sz = 1;
        for (int i = 1; i <= n; ++i) {
            if (p[i] < 0) {
                tp[sz] = p[i];
                te[sz] = e[i];
                ++sz;
            }
        }
        int center = sz;
        tp[sz] = 0; te[sz] = 0; ++sz;
        for (int i = 1; i <= n; ++i) {
            if (p[i] > 0) {
                tp[sz] = p[i];
                te[sz] = e[i];
                ++sz;
            }
        }
        ++n;
        for (int i = 1; i <= n; ++i) p[i] = tp[i], e[i] = te[i];
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= n; ++k) {
                    dp[i][j][k][0] = -inf;
                    dp[i][j][k][1] = -inf;
                }
            }
        }
        dp[1][n][0][0] = dp[1][n][0][1] = 0;
        dp[1][n][1][0] = e[1];
        dp[1][n][1][1] = e[n];
        dp[1][n][2][0] = p[1] - p[n] + e[1] + e[n];
        dp[1][n][2][1] = p[1] - p[n] + e[1] + e[n];
        for (int len = n; len >= 2; --len) {
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                for (int c = 0; c <= n; ++c) {
                    dp[l + 1][r][c][0] = max(dp[l + 1][r][c][0], dp[l][r][c][0] + -abs(p[l] - p[l + 1]) * c);
                    dp[l + 1][r][c + 1][0] = max(dp[l + 1][r][c + 1][0], dp[l][r][c][0] + -abs(p[l] - p[l + 1]) * c + e[l + 1]);
                    dp[l][r - 1][c][1] = max(dp[l][r - 1][c][1], dp[l][r][c][1] + -abs(p[r] - p[r - 1]) * c);
                    dp[l][r - 1][c + 1][1] = max(dp[l][r - 1][c + 1][1], dp[l][r][c][1] + -abs(p[r] - p[r - 1]) * c + e[r - 1]);
                    dp[l + 1][r][c][1] = max(dp[l + 1][r][c][1], dp[l][r][c][0] + -abs(p[r] - p[l]) * c);
                    dp[l + 1][r][c + 1][1] = max(dp[l + 1][r][c + 1][1], dp[l][r][c][0] + -abs(p[r] - p[l]) * c + e[r]);
                    dp[l][r - 1][c][0] = max(dp[l][r - 1][c][0], dp[l][r][c][1] + -abs(p[r] - p[l]) * c);
                    dp[l][r - 1][c + 1][0] = max(dp[l][r - 1][c + 1][0], dp[l][r][c][1] + -abs(p[r] - p[l]) * c + e[l]);
                    // printf("dp[%d][%d][%d][%d] = %lld\n", l, r, c, 0, dp[l][r][c][0]);
                    // printf("dp[%d][%d][%d][%d] = %lld\n", l, r, c, 1, dp[l][r][c][1]);
                }
            }
        }
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 0; k <= n; ++k) {
                    if (i == center) ans = max(ans, dp[i][j][k][0]);
                    if (j == center) ans = max(ans, dp[i][j][k][1]);
                }
            }
        }
        printf("%lld\n", ans);
    }
}
