#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;
int lb[maxn], rb[maxn], ans[maxn], a[maxn];
int pref[maxn][20], suff[maxn][20];

void dvcq(int l, int r, int p, const vector<int> &qr) {
    if (r - l == 1) {
        for (int i = 0; i < (int)qr.size(); ++i) {
            int j = qr[i];
            ans[j] = 1 + (a[l] % p == 0);
        }
        return;
    }
    int m = (l + r) >> 1;
    pref[m][0] = 1;
    for (int i = 1; i < p; ++i) pref[m][i] = 0;
    for (int i = m - 1; i >= l; --i) {
        for (int j = 0; j < p; ++j) pref[i][j] = 0;
        for (int j = 0; j < p; ++j) {
            (pref[i][(j + a[i]) % p] += pref[i + 1][j]) %= mod;
            (pref[i][j] += pref[i + 1][j]) %= mod;
        }
    }

    suff[m - 1][0] = 1;
    for (int i = 1; i < p; ++i) suff[m - 1][i] = 0;
    for (int i = m; i < r; ++i) {
        for (int j = 0; j < p; ++j) suff[i][j] = 0;
        for (int j = 0; j < p; ++j) {
            (suff[i][(j + a[i]) % p] += suff[i - 1][j]) %= mod;
            (suff[i][j] += suff[i - 1][j]) %= mod;
        }
    }

    vector<int> lq, rq;

    for (int i = 0; i < (int)qr.size(); ++i) {
        int j = qr[i];
        if (lb[j] < m && rb[j] > m) {
            // printf("j = %d\n", j);
            for (int k = 0; k < p; ++k)
                (ans[j] += pref[lb[j]][k] * 1ll * suff[rb[j] - 1][(p - k) % p] % mod) %= mod;
        } else if (rb[j] <= m) {
            lq.push_back(j);
        } else {
            rq.push_back(j);
        }
    }

    dvcq(l, m, p, lq);
    dvcq(m, r, p, rq);
}

int main() {
    int n, p; scanf("%d%d", &n, &p);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    int q; scanf("%d", &q);
    vector<int> v;
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &lb[i], &rb[i]);
        --lb[i];
        v.push_back(i);
    }

    dvcq(0, n, p, v);

    for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
    return 0;
}
