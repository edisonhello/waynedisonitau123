#include <bits/stdc++.h>
using namespace std;

int dp[21][11][200];

int main() {
    int n, k, s;
    while (scanf("%d%d%d", &n, &k, &s) != EOF) {
        if (!n && !k && !s) break;
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                for (int p = 0; p <= s; ++p) {
                    if (i + 1 <= n)
                        dp[i + 1][j][p] += dp[i][j][p];
                    if (i + 1 <= n && j + 1 <= k && p + i + 1 <= s)
                        dp[i + 1][j + 1][p + i + 1] += dp[i][j][p];
                }
            }
        }
        printf("%d\n", dp[n][k][s]);
    }
}
