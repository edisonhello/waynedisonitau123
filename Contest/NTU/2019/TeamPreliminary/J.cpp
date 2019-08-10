#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000009;
const int inv2 = 500000005;
const int inv3 = 666666673;

struct data {
    int mx, a1, a2, a3;
    data() : mx(0), a1(0), a2(0), a3(0) {}
    data(int z, int x, int c, int v): mx(z), a1(x), a2(c), a3(v) {}
    void set(int x) {
        mx = a1 = x;
        a2 = 1ll * x * x % mod;
        a3 = 1ll * x * x % mod * x % mod;
    }
    void modify(int e) {
        if (mx == 0) return;
        set(floor(log((long double)(mx)) / log((long double)(e))));
    }
    int get() {
        return (((1ll * a1 * a1 - a2) % mod * inv2 % mod * a1 % mod - 1ll * a1 * a2 % mod + a3) % mod + mod) % mod * inv3 % mod;
    }
    data operator + (const data r) const {
        return data(max(mx, r.mx), (a1 + r.a1) % mod, (a2 + r.a2) % mod, (a3 + r.a3) % mod);
    }
} d[200005 * 4];

int a[200005];

#define mid ((l + r) >> 1)
#define lc ((o * 2) + 1)
#define rc ((o * 2) + 2)
void build(int o, int l, int r) {
    if (l == r) {
        d[o].set(a[l]);
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    d[o] = d[lc] + d[rc];
}

void modify(int o, int l, int r, int ml, int mr, int e) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        if (d[o].mx == 0) return;
        if (l == r) {
            d[o].modify(e);
            return;
        }
    }
    modify(lc, l, mid, ml, mr, e);
    modify(rc, mid + 1, r, ml, mr, e);
    d[o] = d[lc] + d[rc];
}

void change(int o, int l, int r, int m, int x) {
    if (l == r) {
        d[o].set(x);
        return;
    }
    if (m <= mid) change(lc, l, mid, m, x);
    else change(rc, mid + 1, r, m, x);
    d[o] = d[lc] + d[rc];
}

data query(int o, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return data();
    if (ql <= l && r <= qr) return d[o];
    return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(0, 1, n);
    while (q--) {
        int c; cin >> c;
        if (c == 1) {
            int l, r, e; cin >> l >> r >> e;
            modify(0, 1, n, l, r, e);
        }
        if (c == 2) {
            int x, y; cin >> x >> y;
            change(0, 1, n, x, y);
        }
        if (c == 3) {
            int l, r; cin >> l >> r;
            data d = query(0, 1, n, l, r);
            cout << d.get() << '\n';
        }
    }
}
