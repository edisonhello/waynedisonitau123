#include <bits/stdc++.h>
using namespace std;


const int maxn = 305;

long long d[maxn][maxn], dp[maxn][maxn];

void MMWC(int n) {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i) dp[0][i] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) for (int k = 1; k <= n; ++k)
            if (j != k) dp[i][k] = min(dp[i - 1][j] + d[j][k], dp[i][k]);
        for (int j = 1; j <= n; ++j)
            printf("%lld ", dp[i][j]);
        puts("");
    }
    long long au = 1ll << 31, ad = 1;
    for (int i = 1; i <= n; ++i) {
        if (dp[n][i] > 5e8) {
            puts("-1");
            continue;
        }
        long long u = 0, d = 1;
        long long ans = 1e9;
        for (int j = n - 1; j >= 0; --j) {
            printf("dp[n][i] = %lld dp[j][i] = %lld\n", dp[n][i], dp[j][i]);
            ans = min(ans, dp[n][i] - dp[j][i]);
        }
        printf("%lld\n", ans);
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%lld", &d[i][j]);
            if (d[i][j] == -1) d[i][j] = 1e9;
        }
    }
    MMWC(n);
}
