#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int a[maxn], dv[maxn], id[maxn];
vector<int> pr;

void sieve() {
    for (int i = 2; i < maxn; ++i) {
        if (!dv[i]) {
            dv[i] = i;
            id[i] = (int)pr.size();
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] < maxn; ++j) {
            dv[i * pr[j]] = pr[j];
            if (i % pr[j] == 0) break;
        }
    }
}

namespace sgt {
    const int mult = 131;
    const int mod = 1e9 + 123;
    const int maxc = 5e6;
    int st[maxc], lc[maxc], rc[maxc], pw[maxn], tg[maxn], sz;

    void init() {
        pw[0] = 1;
        sz = 0;
        for (int i = 1; i < maxn; ++i) 
            pw[i] = pw[i - 1] * 1ll * mult % mod;

        tg[0] = 0;
        for (int i = 1; i < maxn; ++i)
            tg[i] = (tg[i - 1] * 1ll * mult + 1) % mod;
    }

    int gnode() {
        st[sz] = 0; lc[sz] = rc[sz] = -1;
        return sz++;
    }

    int gnode(int o) {
        st[sz] = st[o];
        lc[sz] = lc[o];
        rc[sz] = rc[o];
        return sz++;
    }

    int build(int l, int r) {
        int o = gnode();
        if (r - l == 1) return o;
        int m = (l + r) >> 1;
        lc[o] = build(l, m);
        rc[o] = build(m, r);
        st[o] = (st[lc[o]] * 1ll * pw[r - m] % mod + st[rc[o]]) % mod;
        return o;
    }

    int modify(int l, int r, int p, int z) {
        int o = gnode(z);
        if (r - l == 1) {
            st[o]++;
            return o;
        }

        int m = (l + r) >> 1;
        if (p < m) lc[o] = modify(l, m, p, lc[z]);
        else rc[o] = modify(m, r, p, rc[z]);
        st[o] = (st[lc[o]] * 1ll * pw[r - m] % mod + st[rc[o]]) % mod;
        return o;
    }

    int find(int l, int r, int ql, int qr) {
        if (r - l == 1) return l;
        int m = (l + r) >> 1;
        int lq = (st[lc[qr]] + mod - st[lc[ql]]) % mod;
        if (lq == tg[m - l]) return find(m, r, rc[ql], rc[qr]);
        else return find(l, m, lc[ql], lc[qr]);
    }
}

int root[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
#endif
    sieve();
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    int c = (int)pr.size();
    sgt::init();
    root[0] = sgt::build(0, c);

    for (int i = 0; i < n; ++i) {
        int x = a[i];
        int last = root[i];
        while (x > 1) {
            int d = dv[x];
            while (x % d == 0) x /= d;
            last = sgt::modify(0, c, id[d], last);
        }
        root[i + 1] = last;
    }

    while (m--) {
        int l, r; scanf("%d%d", &l, &r);
        --l;
        int ans = sgt::find(0, c, root[l], root[r]);
        printf("%d\n", pr[ans]);
    }

    return 0;
}
