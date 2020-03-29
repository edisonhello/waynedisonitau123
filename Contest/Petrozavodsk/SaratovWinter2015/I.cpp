#include <bits/stdc++.h>
using namespace std;

struct node {
    int tag, val;
    node() : tag(-1), val(0) {}
} seg[300005 * 4];

void Push(int o) {
    if (seg[o].tag != -1) {
        seg[o * 2 + 1].tag = seg[o * 2 + 1].val = seg[o].tag;
        seg[o * 2 + 2].tag = seg[o * 2 + 2].val = seg[o].tag;
        seg[o].tag = -1;
    }
}

void Pull(int o) {
    seg[o].val = min(seg[o * 2 + 1].val, seg[o * 2 + 2].val);
}

#define mid ((l + r) >> 1)
void Modify(int o, int l, int r, int ml, int mr, int v) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        seg[o].tag = seg[o].val = v;
        return;
    }
    Push(o);
    Modify(o * 2 + 1, l, mid, ml, mr, v);
    Modify(o * 2 + 2, mid + 1, r, ml, mr, v);
    Pull(o);
}

int Query(int o, int l, int r, int ql, int qr) {
    // cerr << "Query " << o << ' ' << l << ' ' << r << ' ' << ql << ' ' << qr << endl;
    if (l == r) return l;
    Push(o);
    // Cerr << "seg[" << o * 2 + 1 << "].val = " << seg[o * 2 + 1].val << endl;
    // Cerr << "seg[" << o * 2 + 2 << "].val = " << seg[o * 2 + 2].val << endl;
    if (seg[o * 2 + 1].val < ql) return Query(o * 2 + 1, l, mid, ql, qr);
    else return Query(o * 2 + 2, mid + 1, r, ql, qr);
}
#undef mid

int mincall[300005];

int ans[300005];

int main() {
    int n; cin >> n;

    for (int i = 1; i <= n; ++i) mincall[i] = 1000000000;

    for (int i = 1; i <= n; ++i) {
        int t; cin >> t;
        while (t--) {
            int u; cin >> u;
            if (mincall[u] == 1000000000)
                mincall[u] = i;
        }
    }

    for (int i = 1; i <= n; ++i) {
        // cerr << "mincall of " << i << " = " << mincall[i] << endl;

        if (mincall[i] == 1000000000 || mincall[i] == i - 1) {
            ans[i] = 1;
        } else {
            ans[i] = Query(0, 1, n, mincall[i] + 1, i - 1);
        }

        Modify(0, 1, n, ans[i], ans[i], i);
    }

    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << endl;
    
}

