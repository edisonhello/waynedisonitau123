#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
const int mod = 175781251;
const int inv2 = 87890626;
int dp[maxn][maxn], dp2[maxn], dp3[maxn], dp4[2][maxn][maxn], ans[maxn];
int cnk[maxn][maxn], pw[maxn * maxn], pw3[maxn * maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
#endif
    cnk[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        cnk[i][0] = 1;
        for (int j = 1; j < maxn; ++j) {
            cnk[i][j] = cnk[i - 1][j] + cnk[i - 1][j - 1];
            if (cnk[i][j] >= mod) cnk[i][j] -= mod;
        }
    }
    pw[0] = pw3[0] = 1;
    for (int i = 1; i < maxn * maxn; ++i) pw[i] = pw[i - 1] * 2 % mod;
    for (int i = 1; i < maxn * maxn; ++i) pw3[i] = pw3[i - 1] * 3ll % mod;
    dp[1][1] = 1;
    dp[1][0] = 1;
    for (int i = 2; i <= 100; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int k = 1; k <= j; ++k) {
                dp[i][j] += dp[i - 1][j] * 1ll * cnk[j][k] % mod * pw[k] % mod;
                dp[i][j] %= mod;
            }
            if (j) for (int k = 1; k <= i - j; ++k) {
                dp[i][j] += dp[i - 1][j - 1] * 1ll * cnk[i - j][k] % mod * pw[k] % mod;
                dp[i][j] %= mod;
            }
        }
        memset(dp4, 0, sizeof(dp4));
        dp4[0][1][0] = dp4[1][1][0] = 1;
        int n = i;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                for (int k = 1; k + i <= n && k < n - 1; ++k) {
                    for (int r = 0; r <= k; ++r) {
        /* for (int k = 1; k < n - 1; ++k) {
            for (int r = 0; r <= k; ++r) {
                for (int i = 1; i + k <= n; ++i) {
                    for (int j = 0; j <= i; ++j) { */
                        dp4[0][i + k][j + r] += dp4[0][i][j] * 1ll * dp[k][r] % mod * (pw3[r] - 1) % mod * cnk[n - i - 1][k - 1] % mod;
                        dp4[1][i + k][j + r] += dp4[1][i][j] * 1ll * dp[k][r] % mod * (pw3[(k - r)] - 1) % mod * cnk[n - i - 1][k - 1] % mod;
                        // printf("dp4[0][%d][%d] added by %d. i j k r = %d %d %d %d\n", i + k, j + r, dp4[0][i][j] * 1ll * dp[k][r] % mod * (pw3[r] - 1) % mod, i, j, k, r);
                        // printf("dp4[1][%d][%d] added by %d. i j k r = %d %d %d %d\n", i + k, j + r, dp4[1][i][j] * 1ll * dp[k][r] % mod * (pw3[(k - r)] - 1) % mod, i, j, k, r);
                        // if (dp4[i + k][j + r] >= mod) dp4[i + k][j + r] -= mod;
                        dp4[0][i + k][j + r] %= mod;
                        dp4[1][i + k][j + r] %= mod;
                    }
                }
            }
        }
        // printf("i = %d\n", i);
		// for (int i = 1; i <= n; ++i) for (int j = 0; j <= i; ++j) printf("dp4[0][%d][%d] = %d\n", i, j, dp4[0][i][j]);
		// for (int i = 1; i <= n; ++i) for (int j = 0; j <= i; ++j) printf("dp4[1][%d][%d] = %d\n", i, j, dp4[1][i][j]);
        for (int j = 0; j <= i; ++j) (dp[i][j] += dp4[0][i][j] + (j ? dp4[1][i][j - 1] : 0)) %= mod;
        // for (int j = 0; j <= i; ++j) printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
    }
    for (int i = 1; i <= 100; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp2[i] += dp[i][j];
            dp2[i] %= mod;
        }
        dp2[i] = dp2[i] * 1ll * inv2 % mod;
    }
    // printf("dp2[4] = %d\n", dp2[4]);
    for (int x = 1; x <= 100; ++x) {
        memset(dp3, 0, sizeof(dp3));
        dp3[0] = 1;
        for (int i = 0; i < x; ++i) {
            for (int j = 1; i + j <= x; ++j) {
                int select = cnk[x - i - 1][j - 1];
                dp3[i + j] += dp3[i] * 1ll * select % mod * dp2[j] % mod;
                dp3[i + j] %= mod;
            }
        }
        ans[x] = dp3[x];
    }
//    puts("done");
    int n; 
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        printf("%d\n", ans[n]);
    }
    return 0;
}
