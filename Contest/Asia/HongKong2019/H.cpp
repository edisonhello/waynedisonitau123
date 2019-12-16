#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

set<int> seg[500005 * 4];

#define mid ((l + r) >> 1)
void add(int o, int l, int r, int x, int h) {
    seg[o].insert(h);
    if (l == r) return;
    if (x <= mid) add(o * 2 + 1, l, mid, x, h);
    else add(o * 2 + 2, mid + 1, r, x, h);
}

int query(int o, int l, int r, int ql, int qr, int h) {
    if (r < ql || qr < l) return -1;
    if (seg[o].empty()) return -1;
    if (ql <= l && r <= qr) {
        auto it = seg[o].lower_bound(h);
        int a = INT_MAX;
        if (it != seg[o].end()) a = min(a, *it - h);
        if (it != seg[o].begin()) a = min(a, h - *prev(it));
        return a;
    }
    int la = query(o * 2 + 1, l, mid, ql, qr, h);
    int ra = query(o * 2 + 2, mid + 1, r, ql, qr, h);
    if (la == -1) return ra;
    if (ra == -1) return la;
    return min(la, ra);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        for (int i = 0; i <= 4 * n; ++i) seg[i].clear();
        while (m--) {
            int c; cin >> c;
            if (c == 0) {
                int x, h; cin >> x >> h;
                add(0, 1, n, x, h);
            } else {
                int l, r, h; cin >> l >> r >> h;
                cout << query(0, 1, n, l, r, h) << '\n';
            }
        }
    }
}
