#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 5;
const int maxq = 2e4 + 5;
int r[maxn], u[maxq], v[maxq], d[maxn][maxn];
int w[maxq], ans[maxq];

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        printf("Case #%d:\n", tc);
        int n, q; scanf("%d%d", &n, &q);
        for (int i = 0; i < n; ++i) scanf("%d", &r[i]);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                scanf("%d", &d[i][j]);
        }

        for (int i = 0; i < q; ++i) {
            scanf("%d%d%d", &u[i], &v[i], &w[i]);
            --u[i], --v[i];
        }
        vector<int> vt(n);
        iota(vt.begin(), vt.end(), 0);
        sort(vt.begin(), vt.end(), [&](int i, int j) {
            return r[i] < r[j];
        });
        vector<int> qr(q);
        iota(qr.begin(), qr.end(), 0);
        sort(qr.begin(), qr.end(), [&](int i, int j) {
            return w[i] < w[j];
        });

        int p = 0;
        for (int k = 0; k < n; ++k) {
            while (p < q && w[qr[p]] < r[vt[k]]) {
                ans[qr[p]] = d[v[qr[p]]][u[qr[p]]];
                ++p;
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j)
                    d[i][j] = min(d[i][j], d[i][vt[k]] + d[vt[k]][j]);
            }
        }
        while (p < q) {
            ans[qr[p]] = d[v[qr[p]]][u[qr[p]]];
            ++p;
        }
        for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
    }
    return 0;
}
