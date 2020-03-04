#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 5;
const int inf = 1e9;
int d[maxn][maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = inf;
            }
            d[i][i] = 0;
        }
        int m; scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            int x, y, w; scanf("%d%d%d", &x, &y, &w);
            --x, --y;
            d[x][y] = min(d[x][y], w);
            d[y][x] = min(d[y][x], w);
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) 
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
        int ans = 0;
        for (int s = 0; s < n; ++s) {
            int res = inf;
            for (int t = 0; t < n; ++t) {
                int cnt = 0;
                for (int i = 0; i < n; ++i) {
                    if (d[s][i] <= d[t][i]) ++cnt;
                }
                res = min(res, cnt);
            }
            ans = max(ans, res);
        }
        printf("%d\n", ans);
    }
}
