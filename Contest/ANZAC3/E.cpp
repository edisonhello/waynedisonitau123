#include <bits/stdc++.h>
using namespace std;

const int maxn = 300;
int s[maxn], c[maxn];
int l[maxn];
long long dp[maxn][maxn];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    int k, r; scanf("%d%d", &k, &r); 
    for (int i = 1; i <= n; ++i) scanf("%d", &l[i]);

    for (int i = 1; i <= n - 1; ++i) scanf("%d%d", &s[i], &c[i]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            dp[i][j] = 1e18;
    }
    dp[1][1] = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int p = 1; p <= m; ++p) {
                long long d = k * 1ll * abs(p - j);
                if (d <= l[i]) {
                    long long cost = abs(p - j) * 1ll * r + l[i];
                    // if (s[i] + c[i] * 1ll * p <= 0) continue;
                    dp[i + 1][p] = min(dp[i + 1][p], dp[i][j] + cost + s[i] + c[i] * 1ll * p);
                }
            }
        }
    }

    long long ans = 1e18;
    for (int i = 1; i <= m; ++i) {
        long long d = k * 1ll * abs(i - 1);
        if (d <= l[n]) {
            ans = min(ans, dp[n][i] + abs(i - 1) * 1ll * r + l[n]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
