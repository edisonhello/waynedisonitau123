#include <bits/stdc++.h>
using namespace std;

const int maxn = 300 + 5;
const int mod = 1e9 + 7;
int a[maxn], cnk[maxn][maxn], ways[maxn][maxn][maxn], dp[maxn][maxn];

void build() {
    cnk[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        cnk[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            cnk[i][j] = (cnk[i - 1][j] + cnk[i - 1][j - 1]) % mod;
    }
    for (int i = 1; i < maxn; ++i) {
        for (int j = i; j < maxn; ++j) {
            for (int k = 1; k < maxn; ++k) {
                if (i == j) {
                    if (k == 1) ways[i][j][k] = 1;
                } else {
                    if (k == 1) continue;
                    int hole = j - i - 1;
                    ways[i][j][k] = cnk[hole][k - 2];
                }
            }
        }
    }
    for (int i = 1; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) {
            for (int k = 1; k < maxn; ++k)
                (ways[i][j][k] += ways[i - 1][j][k]) %= mod;
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("monotonic.in", "r", stdin);
    freopen("monotonic.out", "w", stdout);
#endif
    build();
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++i) scanf("%d", &a[i]);
    dp[0][n + 1] = 1;
    int s = n;
    for (int i = 0; i < k; ++i) {
        for (int j = 1; j <= n + 1; ++j) {
            if (!dp[i][j]) continue;
            for (int p = 1; p <= s; ++p) {
                int w = ways[j - 1][p][a[i + 1]];
                if (p - a[i + 1] + 1 >= 1)
                    (dp[i + 1][p - a[i + 1] + 1] += 1LL * dp[i][j] * w % mod) %= mod;
            }
        }
        s -= a[i + 1];
    }
    printf("%d\n", dp[k][1]);
}
