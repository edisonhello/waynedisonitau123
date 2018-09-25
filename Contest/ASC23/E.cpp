#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, k, a[maxn], cnt[maxn];
bool v[maxn];

namespace segtree {
    int stx[maxn * 4], stn[maxn * 4];
    void init() {
        for (int i = 0; i < maxn * 4; ++i) {
            stx[i] = 0;
            stn[i] = 0;
        }
    }
    void modify(int l, int r, int p, int v, int o = 0) {
        if (r - l == 1) return stx[o] = v, stn[o] = v, void();
        if (p < (l + r) / 2) modify(l, (l + r) / 2, p, v, o * 2 + 1);
        else modify((l + r) / 2, r, p, v, o * 2 + 2);
        stx[o] = max(stx[o * 2 + 1], stx[o * 2 + 2]);
        stn[o] = min(stn[o * 2 + 1], stn[o * 2 + 2]);
    }
    int queryx(int l, int r, int ql, int qr, int o = 0) {
        if (l >= qr || ql >= r) return -1;
        if (l >= ql && r <= qr) return stx[o];
        return max(queryx(l, (l + r) / 2, ql, qr, o * 2 + 1),
                   queryx((l + r) / 2, r, ql, qr, o * 2 + 2));
    }
    int queryn(int l, int r, int ql, int qr, int o = 0) {
        if (l >= qr || ql >= r) return maxn;
        if (l >= ql && r <= qr) return stn[o];
        return min(queryn(l, (l + r) / 2, ql, qr, o * 2 + 1),
                   queryn((l + r) / 2, r, ql, qr, o * 2 + 2));
    }
}


int main() {
#ifndef LOCAL
    freopen("nice.in", "r", stdin);
    freopen("nice.out", "w", stdout);
#endif
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), v[a[i]] = true;
    segtree::init();
    for (int i = 1; i <= n; ++i) {
        ++cnt[a[i]];
        int x = segtree::queryx(0, n + 1, a[i] + 1, n + 1);
        if (cnt[a[i]] < x - k) {
            printf("%d\n", i - 1);
            return 0;
        }
        int y = segtree::queryn(0, n + 1, 0, a[i]);
        if (y < cnt[a[i]] - k) {
            printf("%d\n", i - 1);
            return 0;
        }
        segtree::modify(0, n + 1, a[i], cnt[a[i]]);
    }
    printf("%d\n", n);
    return 0;
}
