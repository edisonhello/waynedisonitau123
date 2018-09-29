#include <bits/stdc++.h>
using namespace std;

const int maxk = 45, maxn = 1e5 + 5;
const int mod = 1e9 + 7;
const int magic = 3000;
int a[maxn], tab[maxk][maxn], s[maxk][maxn];
pair<int, int> op[maxn];

int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) tab[1][i] = 1;
    for (int i = 2; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) tab[i][j] = (tab[i][j - 1] + tab[i - 1][j]) % mod;
    }
    int sz = 0;
    for (int q = 0; q < m; ++q) {
        int t; scanf("%d", &t);
        if (t == 0) {
            int x, y; scanf("%d%d", &x, &y);
            op[sz++] = make_pair(x, y);
            if (sz > magic) {
                for (int i = 0; i < sz; ++i) (s[0][op[i].first] += op[i].second) %= mod;
                for (int i = 1; i <= k; ++i) {
                    for (int j = 1; j <= n; ++j) s[i][j] = (s[i][j - 1] + s[i - 1][j]) % mod;
                }
                sz = 0;
            }
        } else {
            int x; scanf("%d", &x);
            int ans = s[k][x];
            for (int i = 0; i < sz; ++i) {
                int p, v; tie(p, v) = op[i];
                if (x - p + 1 > 0) (ans += tab[k][x - p + 1] * 1ll * v % mod) %= mod;
            }
            printf("%d\n", ans);
        }
    }
}

