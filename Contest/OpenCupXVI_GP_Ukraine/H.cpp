#include <bits/stdc++.h>
using namespace std;
#define double long double

double p[22], to[22][22];
double at[1005][22];
double tab[1005][1005];

double C(int n, int m) {
    static bool init = false;
    if (!init) {
        tab[0][0] = 1;
        for (int i = 1; i < 1005; ++i) {
            tab[i][0] = tab[i - 1][0];
            for (int j = 1; j < 1005; ++j)
                tab[i][j] = tab[i - 1][j] + tab[i - 1][j - 1];
        }
        init = true;
    }
    return tab[n][m];
}

double fpow(double a, int n) {
    if (a < 1e-9 && n == 0) return 1;
    double res = 1.0;
    while (n > 0) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

double fmem[21][1005];
bool vf[21][1005];
double g(int, int);

double f(int n, int m) {
    if (vf[n][m]) return fmem[n][m];
    if (n == 1 && m == 0) return 1;
    for (int i = 1; i <= n / 2; ++i) 
        for (int j = 0; j < m; ++j) {
            // cout << "n = " << n << " m = " << m << endl;
            // cout << "g = (" << g(i, j) << ", " << g(n - 1, m - 1 - j) << endl;
            // cout << C(n, i) << ' ' << C(m - 1, j) << ' ' << fpow((i * (i - 1) / 2), j) << ' ' << endl;
            double add = g(i, j) * g(n - i, m - 1 - j) * C(n, i) * C(m - 1, j) * fpow(1.0 * (i * (i - 1) / 2) / (n * (n - 1) / 2), j) * fpow(1.0 * (n - i) * (n - i - 1) / 2 / (n * (n - 1) / 2), m - 1 - j) * i * (n - i) / (n * (n - 1) / 2);
            if (i + i == n) add /= 2;
            fmem[n][m] += add;
        }

    vf[n][m] = true;
    return fmem[n][m];
}

double gmem[21][1005];
bool vg[21][1005];
const int magic = 300;
double dp[magic][magic][20][2];

double g(int n, int m) {
    if (n == 1) {
        if (m == 0) return 1;
        return 0;
    }
    
    if (vg[n][m]) return gmem[n][m];
    for (int i = 0; i <= m; ++i) gmem[n][m] += f(n, i);
    vg[n][m] = true;
    return gmem[n][m];
}

void test() {
    int n, m; while (cin >> n >> m) {
        cout << f(n, m) << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    // test();
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0; i < n; ++i) {
        int m; cin >> m; 
        for (int j = 0; j < m; ++j) {
            int t; cin >> t; --t;
            to[i][t] = 1. / m;
        }
    }
    /* for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cerr << to[i][j] << ' ';
        cerr << endl;
    } */
    dp[0][0][0][0] = 1.0;
    for (int i = 0; i < magic - 1; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int pp = 0; pp < n; ++pp) {
                for (int x = 0; x < n; ++x) {
                    dp[i + 1][j + 1][x][1] += (dp[i][j][pp][0] + dp[i][j][pp][1]) * to[pp][x] * p[pp];
                    dp[i + 1][j][x][0] += (dp[i][j][pp][0] + dp[i][j][pp][1])  * to[pp][x] * (1 - p[pp]);
                }
            }
        }
    }

    double ans = 0.0;
    for (int i = 1; i < magic; ++i) for (int j = 0; j <= i; ++j) for (int k = 0; k < n; ++k) {
        // printf("f(%d, %d) = %.20lf\n", n, j, f(n, j));
        // printf("dp[%d][%d][%d] = %.20lf\n", i, j, k, dp[i][j][k]);
        // printf("add = %.20lf\n", dp[i][j][k] * f(n, j) * (i));
        ans += dp[i][j][k][1] * f(n, j) * (i);
        // printf("ans = %.20lf\n", ans);
        // cerr << i << " " << j << " : " << at[i][j] << " * " << p[j] << " * " << f(n, i) << endl;
    }
    cout << fixed << setprecision(20) << ans << endl;

}
