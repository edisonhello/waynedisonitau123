#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
using matrix = vector<vector<int>>;

matrix mult(matrix a, matrix b) {
    int n = (int)a.size();
    matrix c(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                c[i][j] += a[i][k] * 1ll * b[k][j] % mod;
                c[i][j] %= mod;
            }
        }
    }
    return c;
}

matrix fpow(matrix a, long long m) {
    int n = (int)a.size();
    matrix res(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1;
    while (m > 0) {
        if (m & 1)
            res = mult(res, a);
        a = mult(a, a);
        m >>= 1;
    }
    return res;
}

const int maxn = 3e5 + 5;
int d[maxn], pref[maxn];

int main() {
    int tc; scanf("%d", &tc);
    while (tc--) {
        int n, k; long long t; scanf("%d%d%lld", &n, &k, &t);
        vector<int> lev, rho;
        set<int> used;
        lev.push_back(n);
        used.insert(0);
        for (int i = 1; i <= k; ++i) {
            int x; scanf("%d", &x);
            if (lev.size() && lev.back() == x) {
                used.erase(i - 1);
                used.insert(i);
            } else {
                used.insert(i);
                lev.push_back(x);
            }
        }
        for (int i = 1; i <= n; ++i) scanf("%d", &d[i]);
        for (int i = 0; i <= k; ++i) {
            int x; scanf("%d", &x);
            if (used.count(i))
                rho.push_back(x);
        }
        int m = (int)rho.size();
        for (int i = m - 1; i >= 1; --i) {
            rho[i] -= rho[i - 1];
            rho[i] %= mod;
            rho[i] += mod;
            rho[i] %= mod;
        }

        matrix mat(m, vector<int>(m, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i; ++j) {
                mat[i][j] = lev[i] * 1ll * rho[j] % mod;
            }
            for (int j = i; j < m; ++j) {
                mat[i][i] += lev[j] * 1ll * rho[j] % mod;
                mat[i][i] %= mod;
            }
        }

        /* for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j)
                printf("%d ", mat[i][j]);
            puts("");
        } */

        // printf("done construction\n");
        mat = fpow(mat, t);
        // printf("done fpow\n");

        for (int i = 1; i <= n; ++i) pref[i] = (pref[i - 1] + d[i]) % mod;
        for (int i = 1; i <= n; ++i) {
            int ans = 0;
            for (int j = 0; j < m; ++j) {
                // printf("lev = %d\n", lev[j]);
                int l = (i - 1) / lev[j] * lev[j];
                int r = (i - 1) / lev[j] * lev[j] + lev[j];
                // printf("i = %d j = %d l = %d r = %d\n", i, j, l, r);
                int s = (pref[r] + mod - pref[l]) % mod;
                ans += s * 1ll * mat[m - 1][j] % mod;
                ans %= mod;
            }
            printf("%d ", ans);
        }
        puts("");
    }

    return 0;
}
