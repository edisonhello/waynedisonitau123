#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int t[maxn], z[maxn];
int dp[maxn][maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &t[i]);
    int m; scanf("%d", &m);
    for (int i = 1; i <= 100; ++i) z[i] = 25;
    for (int i = 0; i < m; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        z[x] = min(z[x], y);
    }

    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) dp[i][j] = 1e9;
    }

    dp[0][0] = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j <= n; ++j) {
            int nxt = j + 1;
            if (nxt > n) nxt = 1;
            if (t[nxt] <= z[i + 1]) dp[i + 1][nxt] = min(dp[i + 1][nxt], dp[i][j]);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][j] + 1);
        }
    }
    int ans = 1e9;
    for (int i = 0; i <= n; ++i) ans = min(ans, dp[100][i]);
    printf("%d\n", ans);
    return 0;
}
