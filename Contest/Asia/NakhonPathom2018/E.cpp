#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int a[maxn], dp[maxn][3][2][3];

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int a = 0; a < 2; ++a) {
                    for (int b = 0; b < 3; ++b) 
                        dp[i][j][a][b] = -1e9;
                }
            }
        }
        sort(a + 1, a + n + 1);
        dp[0][0][0][0] = 0;
        a[0] = a[1];
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int p = 0; p < 3; ++p) {
                    for (int q = 0; q < 3; ++q) {
                        int x = a[i] + (p == 0 ? 0 : p == 1 ? -1 : 1);
                        int y = a[i - 1] + (q == 0 ? 0 : q == 1 ? -1 : 1);
                        if (p == 0) dp[i][j][1][p] = max(dp[i][j][1][p], 1);
                        else if (j > 0) dp[i][j][1][p] = max(dp[i][j][1][p], 1);
                        if (abs(x - y) > 2) continue;
                        if (p == 0) {
                            dp[i][j][1][p] = max(dp[i][j][1][p], dp[i - 1][j][1][q] + 1);
                        } else {
                            if (j > 0) {
                                dp[i][j][1][p] = max(dp[i][j][1][p], dp[i - 1][j - 1][1][q] + 1);
                            }
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int a = 0; a < 2; ++a) {
                    for (int b = 0; b < 3; ++b)
                        ans = max(ans, dp[i][j][a][b]);
                }
            }
        }
        printf("Case %d: %d\n", tc, ans);
    }
}
