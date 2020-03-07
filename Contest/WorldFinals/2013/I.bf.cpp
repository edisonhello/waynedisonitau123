#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int h[505][505];
int sp[10][10][505][505];
int spr[10][505][505];
int spc[10][505][505];

int main() {
    int a, b, n, m; cin >> a >> b >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        cin >> h[i][j];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sp[0][0][i][j] = h[i + 1][j + 1];
            spr[0][i][j] = h[i + 1][j + 1];
            spc[0][i][j] = h[i + 1][j + 1];
        }
    }
    for (int i = 1; (1 << i) <= n; ++i) {
        for (int a = 0; a + (1 << i) <= n; ++a) {
            for (int b = 0; b < m; ++b) {
                spr[i][a][b] = min(spr[i - 1][a][b], spr[i - 1][a + (1 << (i - 1))][b]);
            }
        }
    }
    for (int i = 1; (1 << i) <= m; ++i) {
        for (int a = 0; a + (1 << i) <= m; ++a) {
            for (int b = 0; b < n; ++b) {
                spc[i][b][a] = min(spc[i - 1][b][a], spc[i - 1][b][a + (1 << (i - 1))]);
            }
        }
    }
    for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 1; (1 << j) <= m; ++j) {
            for (int a = 0; a + (1 << i) <= n; ++a) {
                for (int b = 0; b + (1 << j) <= m; ++b) {
                    sp[i][j][a][b] = min({
                        sp[i - 1][j - 1][a][b],
                        sp[i - 1][j - 1][a + (1 << (i - 1))][b],
                        sp[i - 1][j - 1][a][b + (1 << (j - 1))],
                        sp[i - 1][j - 1][a + (1 << (i - 1))][b + (1 << (j - 1))]});
                }
            }
        }
    }
    long long mx = 0;

    auto Query = [&](int a, int b, int c, int d) {
        int p = 31 - __builtin_clz(b - a + 1);
        int q = 31 - __builtin_clz(d - c + 1);
        if (a == b) {
            return min(spc[q][a][c], spc[q][a][d - (1 << q) + 1]);
        } 
        if (c == d) {
            return min(spr[p][a][c], spr[p][b - (1 << p) + 1][c]);
        }
        return min({
                sp[p][q][a][c],
                sp[p][q][b - (1 << p) + 1][c],
                sp[p][q][a][d - (1 << q) + 1],
                sp[p][q][b - (1 << p) + 1][d - (1 << q) + 1]
                });
    };

    auto Solve = [&] () {
        for (int aa = 1; aa <= a; ++aa) {
            for (int i = 1; i + aa - 1 <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    auto Calc = [&] (const int bb) -> long long {
                        int mn = INT_MAX;
                        // mn = rand() % 100000001;
                        mn = Query(i - 1, i - 1 + aa - 1, j - 1, j - 1 + bb - 1);
                        // for (int ii = i; ii < i + aa; ++ii) {
                        //     for (int jj = j; jj < j + bb; ++jj) {
                        //         mn = min(mn, h[ii][jj]);
                        //     }
                        // }
                        long long up = aa * bb * mn;
                        long long dn = m * n - aa * bb;
                        long long hh = (up / dn) - (up % dn ? 0 : 1);
                        hh = max(hh, 0ll);
                        return aa * bb * (mn + hh);
                    };
                    int l = 1, r = min(m - j + 1, b);
                    for (int bb = l; bb <= r; ++bb) {
                        long long v = Calc(bb);
                        // cerr << aa << ' ' << bb << ' ' << i << ' ' << j << ' ' << v << endl;
                        mx = max(mx, v);
                    }
                }
            }
        }
    };

    Solve();
    swap(a, b);
    Solve();

    cout << mx << endl;
}
