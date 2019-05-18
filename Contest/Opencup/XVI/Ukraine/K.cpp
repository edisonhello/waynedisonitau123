#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
long long s[maxn], p[maxn], dp[2][maxn];
int f[maxn];

long long calc(int l, int r) {
    // printf("solve l = %d r = %d -> %lld\n", l, r, p[r] - p[l] - l * 1ll * s[r] + l * 1ll * s[l]);
    return p[r] - p[l] - l * 1ll * s[r] + l * 1ll * s[l];
}

void solve(int l, int r, int tl, int tr, long long *cur, long long *prv) {
    if (l > r) return;
    int m = (l + r) >> 1;
    cur[m] = 1e18;
    int tm = -1;
    for (int i = tl; i <= min(m - 1, tr); ++i) {
        long long d = prv[i] + calc(i, m);
        if (d < cur[m]) {
            cur[m] = d;
            tm = i;
        }
    }
    solve(l, m - 1, tl, tm, cur, prv);
    solve(m + 1, r, tm, tr, cur, prv);
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &f[i]);
        s[i] = s[i - 1] + f[i];
        p[i] = p[i - 1] + f[i] * 1ll * i;
    }

    for (int i = 1; i <= n; ++i) dp[0][i] = 1e18;
    for (int i = 1; i <= m; ++i) {
        solve(1, n, 0, n - 1, dp[i & 1], dp[i & 1 ^ 1]);
    }
    printf("%lld\n", dp[m & 1][n]);
    return 0;
}
