#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
int a[maxn][maxn], s[maxn][maxn];
char buf[2 * maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        fgets(buf, 2 * maxn - 1, stdin);
        for (int i = 0; i < n; ++i) {
            fgets(buf, 2 * maxn - 1, stdin);
            for (int j = 0, k = 1; j < 2 * m - 1; j += 2, ++k) {
                a[i + 1][k] = buf[j] - '0';
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) 
                s[i][j] = s[i - 1][j] + s[i][j - 1] + a[i][j] - s[i - 1][j - 1];
        }

        auto query = [&](int u, int l, int d, int r) {
            return s[d][r] + s[u - 1][l - 1] - s[d][l - 1] - s[u - 1][r];
        };

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int p = 0;
                for (int d = 10; d >= 0; --d) {
                    int q = p + (1 << d);
                    if (i + q - 1 <= n && j + q - 1 <= m) {
                        if (query(i, j, i + q - 1, j + q - 1) <= 1) p = q;
                    }
                }
                ans = max(ans, p);
            }
        }
        printf("%d\n", ans);
    }
}
