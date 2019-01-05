#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
int dp[maxn][11][3], a[maxn];

int main() {
    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= 10; ++j) {
                dp[i][j][0] = 0;
                dp[i][j][1] = 0;
                dp[i][j][2] = 0;
            }
        }
        dp[0][0][2] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                dp[i][j][1] = dp[i - 1][j][2];
                if (j) dp[i][j][0] = dp[i - 1][j - 1][2];
                dp[i][j][2] = (dp[i][j][1] + dp[i][j][0]) % mod;
                for (int k = 1; k <= 10; ++k) {
                    if (i - k >= 1 && j - k >= 0 && a[i] == a[i - k]) {
                        dp[i][j][2] += mod - dp[i - k][j - k][1];
                        dp[i][j][2] %= mod;
                        break;
                    }
                }
                // printf("dp[%d][%d][0] = %d\n", i, j, dp[i][j][0]);
                // printf("dp[%d][%d][1] = %d\n", i, j, dp[i][j][1]);
                // printf("dp[%d][%d][2] = %d\n", i, j, dp[i][j][2]);
            }
        }
        printf("%d\n", dp[n][m][2]);
    }
}
