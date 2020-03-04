#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
const int inf = 1e9;
char a[maxn], b[maxn];
int sa[26], ea[26], sb[26], eb[26];
int xa[maxn], ya[maxn], xb[maxn], yb[maxn];
int dp[maxn][maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%s", a + 1);
        scanf("%s", b + 1);
        int n = strlen(a + 1), m = strlen(b + 1);
        for (int i = 0; i < 26; ++i) {
            sa[i] = n + 1, ea[i] = -1;
            sb[i] = m + 1, eb[i] = -1;
        }
        for (int i = 1; i <= n; ++i) {
            if (sa[a[i] - 'A'] == n + 1) sa[a[i] - 'A'] = i;
            ea[a[i] - 'A'] = i;
        }
        for (int i = 1; i <= m; ++i) {
            if (sb[b[i] - 'A'] == m + 1) sb[b[i] - 'A'] = i;
            eb[b[i] - 'A'] = i;
        }
        /* for (int i = 0; i < 26; ++i) {
            printf("sa[%d] = %d\n", i, sa[i]);
            printf("ea[%d] = %d\n", i, ea[i]);
            printf("sb[%d] = %d\n", i, sb[i]);
            printf("eb[%d] = %d\n", i, eb[i]);
        } */
        for (int i = 0; i <= n; ++i) {
            xa[i] = ya[i] = 0;
            for (int j = 0; j < 26; ++j) {
                if (sa[j] <= i) xa[i] ^= (1 << j);
                if (ea[j] > i) ya[i] ^= (1 << j);
            }
        }
        for (int i = 0; i <= m; ++i) {
            xb[i] = yb[i] = 0;
            for (int j = 0; j < 26; ++j) {
                if (sb[j] <= i) xb[i] ^= (1 << j);
                if (eb[j] > i) yb[i] ^= (1 << j);
            }
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) dp[i][j] = inf;
        }
        dp[0][0] = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                int x = (xa[i] | xb[j]), y = (ya[i] | yb[j]);
                int cost = __builtin_popcount(x & y);
                /* for (int k = 0; k < 26; ++k) {
                    if ((sa[k] <= i || sb[k] <= j) && (eb[k] > j || ea[k] > i)) ++cost;
                    // if (sa[k] < i && ea[k] >= i || sb[k] < j && eb[k] >= j) ++cost;
                } */
                dp[i][j] += cost;
                if (i + 1 <= n) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
                if (j + 1 <= m) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j]);
                // printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
                /* if (i + 1 <= n) {
                    int cost = 0;
                    for (int k = 0; k < 26; ++k) {
                        if ((sa[k] < i + 1 || sb[k] <= j) && (eb[k] > j || ea[k] >= i + 1)) ++cost;
                    }
                    dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + cost);
                }
                if (j + 1 <= m) {
                    int cost = 0;
                    for (int k = 0; k < 26; ++k) {
                        if ((sb[k] < j + 1 || sa[k] <= i) && (ea[k] > i || eb[k] >= j + 1)) ++cost;
                    }
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + cost);
                } */
            }
        }
        printf("%d\n", dp[n][m]);
    }
    return 0;
}
