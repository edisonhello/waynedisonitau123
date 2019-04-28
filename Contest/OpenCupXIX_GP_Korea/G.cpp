#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6;
const long long inf = 1e18;
long long dp[2][10][20][3];
int w[maxn];

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 20; ++k) {
                dp[i][j][k][0] = inf;
                dp[i][j][k][1] = inf;
                dp[i][j][k][2] = inf;
            }
        }
    }
    dp[0][k][9][2] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 20; ++k) {
                dp[i & 1][j][k][0] = inf;
                dp[i & 1][j][k][1] = inf;
                dp[i & 1][j][k][2] = inf;
            }
        }
        for (int j = 0; j < 10; ++j) {
            for (int k = -9; k <= 9; ++k) {
                // choose i
                dp[i & 1][j][k + 9][1] = min(dp[i & 1][j][k + 9][1], dp[i & 1 ^ 1][j][k + 9][0] + w[i]);
                dp[i & 1][j][k + 9][1] = min(dp[i & 1][j][k + 9][1], dp[i & 1 ^ 1][j][k + 9][1] + w[i]);
                dp[i & 1][j][k + 9][1] = min(dp[i & 1][j][k + 9][1], dp[i & 1 ^ 1][j][k + 9][2] + w[i]);
                if (j && k - 1 >= -9) {
                    // guarded by someone else
                    dp[i & 1][j - 1][k - 1 + 9][1] = min(dp[i & 1][j - 1][k - 1 + 9][1], dp[i & 1 ^ 1][j][k + 9][0]);
                    dp[i & 1][j - 1][k - 1 + 9][1] = min(dp[i & 1][j - 1][k - 1 + 9][1], dp[i & 1 ^ 1][j][k + 9][1]);
                    dp[i & 1][j - 1][k - 1 + 9][1] = min(dp[i & 1][j - 1][k - 1 + 9][1], dp[i & 1 ^ 1][j][k + 9][2]);
                }
                if (k - 1 >= -9) {
                    // guarded by someone else
                    dp[i & 1][j][k - 1 + 9][1] = min(dp[i & 1][j][k - 1 + 9][1], dp[i & 1 ^ 1][j][k + 9][0]);
                    dp[i & 1][j][k - 1 + 9][1] = min(dp[i & 1][j][k - 1 + 9][1], dp[i & 1 ^ 1][j][k + 9][1]);
                    dp[i & 1][j][k - 1 + 9][1] = min(dp[i & 1][j][k - 1 + 9][1], dp[i & 1 ^ 1][j][k + 9][2]);
                }
                // not choose i but i is protected
                dp[i & 1][j][k + 9][2] = min(dp[i & 1][j][k + 9][2], dp[i & 1 ^ 1][j][k + 9][1]);
                // not choose i and i is dangerous
                dp[i & 1][j][k + 9][0] = min(dp[i & 1][j][k + 9][0], dp[i & 1 ^ 1][j][k + 9][2]);
                if (j && k + 1 <= 9) {
                    dp[i & 1][j - 1][k  + 1 + 9][2] = min(dp[i & 1][j - 1][k + 1 + 9][2], dp[i & 1 ^ 1][j][k + 9][1] + w[i]);
                    dp[i & 1][j - 1][k  + 1 + 9][0] = min(dp[i & 1][j - 1][k + 1 + 9][0], dp[i & 1 ^ 1][j][k + 9][2] + w[i]);
                }
                /* if (j > 1 || k > 1) continue;
                printf("dp[%d][%d][%d][0] = %lld\n", i - 1, j, k, dp[i & 1 ^ 1][j][k][0]);
                printf("dp[%d][%d][%d][1] = %lld\n", i - 1, j, k, dp[i & 1 ^ 1][j][k][1]);
                printf("dp[%d][%d][%d][2] = %lld\n", i - 1, j, k, dp[i & 1 ^ 1][j][k][2]); */
            }
        }
    }
    long long ans = inf;
    for (int i = 0; i <= k; ++i) {
        ans = min(ans, dp[n & 1][i][9][1]);
        ans = min(ans, dp[n & 1][i][9][2]);
    }
    printf("%lld\n", ans);
}
