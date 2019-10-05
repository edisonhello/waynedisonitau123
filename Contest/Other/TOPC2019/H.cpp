#include <bits/stdc++.h>
using namespace std;
#define data sfhueoi

struct data {
    int ans, lans, rans, lv, rv, len;
    data() : ans(1), lans(1), rans(1), lv(0), rv(0), len(1) {}
    void modify(int x) {
        lv = rv = x;
    }
};

data operator + (const data &a, const data &b) {
    data r;
    r.len = a.len + b.len;
    r.ans = max(a.ans, b.ans);
    r.lans = a.lans;
    r.rans = b.rans;
    r.lv = a.lv;
    r.rv = b.rv;
    if (!(a.rv < 0 && b.lv > 0)) { //connect
        if (a.lans == a.len) r.lans += b.lans;
        if (b.rans == b.len) r.rans += a.rans;
        r.ans = max(r.ans, max(r.lans, r.rans));
        r.ans = max(r.ans, a.rans + b.lans);
    }
    return r;
}

struct node {
    node *l, *r;
    data d;
    node() : l(0), r(0), d() {}
} *root;

int h[100005];

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) return;
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
}

void modify(node *now, int l, int r, int x, int v) {
    if (l == r) {
        now->d.modify(v);
        return;
    }
    if (x <= mid) modify(now->l, l, mid, x, v);
    else modify(now->r, mid + 1, r, x, v);
    now->d = now->l->d + now->r->d;
}

data query(node *now, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return now->d;
    if (qr <= mid) return query(now->l, l, mid, ql, qr);
    if (mid < ql) return query(now->r, mid + 1, r, ql, qr);
    return query(now->l, l, mid, ql, qr) + query(now->r, mid + 1, r, ql, qr);
}

void del(node *now) {
    if (!now) return;
    if (now->l) del(now->l);
    if (now->r) del(now->r);
    delete now;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        build(root = new node(), 0, n - 2);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        for (int i = 0; i < n - 1; ++i) {
            modify(root, 0, n - 2, i, h[i + 1] - h[i]);
        }
        int q; cin >> q; while (q--) {
            int c; cin >> c; 
            if (c == 1) {
                int i, d; cin >> i >> d;
                h[i] += d;
                if (i != 0) {
                    modify(root, 0, n - 2, i - 1, h[i] - h[i - 1]);
                } 
                if (i != n - 2) {
                    modify(root, 0, n - 2, i, h[i + 1] - h[i]);
                }
            } else {
                int l, r; cin >> l >> r;
                if (l == r) cout << 1 << '\n';
                else cout << query(root, 0, n - 2, l, r - 1).ans + 1 << '\n';
            }
        }
        del(root);
    }
}
