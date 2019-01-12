#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
long long dp[2][maxn][maxn * maxn];
int a[maxn], b[maxn], c[maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]);
        reverse(a + 1, a + n + 1);
        reverse(b + 1, b + n + 1);
        reverse(c + 1, c + n + 1);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n * n; ++j) {
                dp[0][i][j] = -1e18;
                dp[1][i][j] = -1e18;
            }
        }
        dp[0][0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= n * n; ++k)
                    dp[i & 1][j][k] = -1e18;
            }
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= n * n; ++k) {
                    int sum = i * (i - 1) / 2;
                    if (j && k >= i)
                        dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[i & 1 ^ 1][j - 1][k - i] + a[i]);
                    dp[i & 1][j][k] = max(dp[i & 1][j][k], dp[i & 1 ^ 1][j][k] + max(j * 1ll * c[i], b[i] * 1ll * (i * j - k)));
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n * n; ++j)
                ans = max(ans, dp[n & 1][i][j]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
