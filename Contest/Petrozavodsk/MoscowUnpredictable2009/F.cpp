#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;
int cnk[maxn][maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("polynomial.in", "r", stdin);
    freopen("polynomial.out", "w", stdout);
#endif
    int m; scanf("%d", &m);
    vector<pair<int, int>> dv;
    int v = m;
    for (int i = 2; i <= v; ++i) {
        int c = 0;
        while (v % i == 0) {
            c += 1;
            v /= i;
        }
        if (c > 0) dv.emplace_back(i, c);
    }

    cnk[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        cnk[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            cnk[i][j] = cnk[i - 1][j] + cnk[i - 1][j - 1];
            cnk[i][j] %= m;
        }
    }

    vector<int> ans = {1};

    auto mult = [m](const vector<int> &a, const vector<int> &b) {
        vector<int> res(a.size() + b.size() - 1, 0);
        for (int i = 0; i < (int)a.size(); ++i) {
            for (int j = 0; j < (int)b.size(); ++j) {
                res[i + j] += a[i] * 1ll * b[j] % m;
                res[i + j] %= m;
            }
        }
        return res;
    };

    for (int i = 0; i < (int)dv.size(); ++i) {
        int p = dv[i].first, q = dv[i].second;    
        // printf("p = %d q = %d\n", p, q);
        vector<int> poly(p * q + 1, 0);
        for (int j = 0, v = p * q; j <= q; ++j, v -= p) {
            int coef = cnk[q][j];
            if (j & 1) coef = (m - coef) % m;
            poly[v + j] = coef;
        }
        // puts("poly");
        // for (int j = 0; j < (int)poly.size(); ++j) printf("%d ", poly[j]); puts("");
        ans = mult(ans, poly);
    }

    printf("%d\n", (int)ans.size() - 1);
    for (int i = (int)ans.size() - 1; i >= 0; --i) printf("%d ", ans[i]);
    puts("");
}
