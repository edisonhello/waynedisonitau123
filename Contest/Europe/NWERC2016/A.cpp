#include <bits/stdc++.h>
using namespace std;

const int maxn = 50, maxm = 400 + 5;
char s[maxn][maxm], t[maxn][maxm];
int dp[maxn][maxn][maxm][10];
array<int, 3> fr[maxn][maxn][maxm][10];
int cnt[maxn][maxm][10], n, m;
bool v[maxn][maxn][maxm][10];

int dfs(int l, int r, int k, int d) {
    if (l > r) return 0;
    if (k > m) return 0;
    // if (l == r) return 0;
    if (v[l][r][k][d]) return dp[l][r][k][d];
    dp[l][r][k][d] = 1e9;
    for (int i = 0; i < 10; ++i) {
        int dd = dfs(l, r, k + 1, i) + (r - l + 1) - (cnt[r][k][d] - cnt[l - 1][k][d]);
        if (dd < dp[l][r][k][d]) {
            dp[l][r][k][d] = dd;
            fr[l][r][k][d] = {l, -1, i};
        }
    }

    for (int mid = r; mid > l; --mid) {
        int bot = 1e9, nxt = 1e9;
        int bi = -1, ni = -1;
        for (int c = 0; c < d; ++c) {
            int dd = dfs(l, mid - 1, k, c);
            if (dd < bot) {
                bot = dd;
                bi = c;
            }
        }
        for (int c = 0; c < 10; ++c) {
            int dd = dfs(mid, r, k + 1, c);
            if (dd < nxt) {
                nxt = dd;
                ni = c;
            }
        }
        int cost = (r - mid + 1) - (cnt[r][k][d] - cnt[mid - 1][k][d]);
        if (bot + nxt + cost < dp[l][r][k][d]) {
            dp[l][r][k][d] = bot + nxt + cost;
            fr[l][r][k][d] = {mid, bi, ni};
        }
    }
    // printf("dp[%d][%d][%d][%d] = %d\n", l, r, k, d, dp[l][r][k][d]);
    v[l][r][k][d] = true;
    return dp[l][r][k][d];
}

void rec(int l, int r, int k, int d) {
    if (l > r) return;
    if (k > m) return;
    if (l == r) {
        t[l][k] = (char)(d + '0');
        return;
    }
    for (int i = fr[l][r][k][d][0]; i <= r; ++i) t[i][k] = (char)(d + '0');
    rec(l, fr[l][r][k][d][0] - 1, k, fr[l][r][k][d][1]);
    rec(fr[l][r][k][d][0], r, k + 1, fr[l][r][k][d][2]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int d = 0; d < 10; ++d) cnt[i][j][d] = cnt[i - 1][j][d];
            cnt[i][j][s[i][j] - '0']++;
        }
    }

    int ans = 1e9, z = -1;
    for (int i = 0; i < 10; ++i) {
        int dd = dfs(1, n, 1, i);
        if (dd < ans) {
            ans = dd;
            z = i;
        }
    }
    // cout << "ans = " << ans << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) t[i][j] = s[i][j];
    }
    rec(1, n, 1, z);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) printf("%c", t[i][j]);
        puts("");
    }
    return 0;
}
