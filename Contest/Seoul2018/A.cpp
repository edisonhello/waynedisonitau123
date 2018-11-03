#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int ux[maxn], uy[maxn], vx[maxn], vy[maxn];
int l[maxn], r[maxn];
vector<int> st[maxn], ed[maxn];

namespace segtree {
    int mx[maxn * 4], tg[maxn * 4];
    void init() {
        for (int i = 0; i < maxn * 4; ++i)
            mx[i] = 0, tg[i] = 0;
    }
    void push(int o) {
        if (tg[o] == 0) return;
        mx[o * 2 + 1] += tg[o], tg[o * 2 + 1] += tg[o];
        mx[o * 2 + 2] += tg[o], tg[o * 2 + 2] += tg[o];
        tg[o] = 0;
    }
    void modify(int l, int r, int ql, int qr, int v, int o = 0) {
        if (r - l > 1) push(o);
        if (l >= qr || ql >= r) return;
        if (l >= ql && r <= qr) return mx[o] += v, tg[o] += v, void();
        modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
        modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
        mx[o] = max(mx[o * 2 + 1], mx[o * 2 + 2]);
    }
    int query(int l, int r, int ql, int qr, int o = 0) {
        if (r - l > 1) push(o);
        if (l >= qr || ql >= r) return 0;
        if (l >= ql && r <= qr) return mx[o];
        return query(l, (l + r) >> 1, ql, qr, o * 2 + 1) +
               query((l + r) >> 1, r, ql, qr, o * 2 + 2);
    }
}

int main() {
    int n; scanf("%d", &n);
    vector<int> ds;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &ux[i], &uy[i], &vx[i], &vy[i]);
        l[i] = vy[i];
        r[i] = uy[i];
        ds.push_back(l[i]);
        ds.push_back(r[i]);
    }
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < n; ++i) {
        l[i] = lower_bound(ds.begin(), ds.end(), l[i]) - ds.begin();
        r[i] = lower_bound(ds.begin(), ds.end(), r[i]) - ds.begin();
        st[l[i]].push_back(i);
        ed[r[i]].push_back(i);
    }
    int ans = 0, got = 0;
    for (int i = 0; i < n; ++i)
        segtree::modify(0, maxn, l[i], r[i] + 1, 1);
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < (int)st[i].size(); ++j)
            segtree::modify(0, maxn, l[st[i][j]], r[st[i][j]] + 1, -1), ++got;
        ans = max(ans, got + segtree::query(0, maxn, 0, maxn));
        for (int j = 0; j < (int)ed[i].size(); ++j) --got;
    }
    printf("%d\n", ans);
    return 0;
}
