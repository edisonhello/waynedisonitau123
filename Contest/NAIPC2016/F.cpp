#include <bits/stdc++.h>
using namespace std;

const int maxk = 200;
const int maxn = 1e4 + 5;
const int mod = 1e9 + 7;
int dp[2][maxn], sum[maxn];

int main() {
    int n, w, h; scanf("%d%d%d", &n, &w, &h);
    dp[0][0] = 1;
    for (int i = 1; i <= w; ++i) {
        sum[0] = dp[i & 1 ^ 1][0];
        for (int j = 1; j <= n; ++j) sum[j] = (sum[j - 1] + dp[i & 1 ^ 1][j]) % mod;
        for (int j = 0; j <= n; ++j) {
            int l = max(0, j - h), r = j;
            if (l == 0) dp[i & 1][j] = sum[r];
            else dp[i & 1][j] = (sum[r] + mod - sum[l - 1]) % mod;
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) (ans += dp[w & 1][i]) %= mod;
    for (int i = 0; i <= h; ++i) {
        if (i * w <= n) (ans += mod - 1) %= mod;
    }
    printf("%d\n", ans);
    return 0;
}
