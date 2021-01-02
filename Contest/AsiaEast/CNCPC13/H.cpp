#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    long long ll, rr;
    long long tag, ans;
    node() : l(0), r(0), ll(0), rr(0), tag(0), ans(0) {}
    void modify(int v) {
        tag += v;
        ans += v;
        ll += v;
        rr += v;
    }
    void push() {
        if (tag) {
            l->modify(tag);
            r->modify(tag);
            tag = 0;
        }
    }
    void pull() {
        ans = l->ans + r->ans - min(l->rr, r->ll);
        ll = l->ll;
        rr = r->rr;
    }
    void set(int x) {
        ll = rr = ans = x;
        tag = 0;
    }
} *root;

int a[100005];

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) {
        now->set(a[l]);
        return;
    }
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
    now->pull();
}

void modify(node *now, int l, int r, int ml, int mr, int v) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        now->modify(v);
        return;
    }
    now->push();
    modify(now->l, l, mid, ml, mr, v);
    modify(now->r, mid + 1, r, ml, mr, v);
    now->pull();
}

tuple<long long, long long, long long> query(node *now, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return make_tuple(now->ll, now->ans, now->rr);
    }
    now->push();

    if (qr <= mid) return query(now->l, l, mid, ql, qr);
    else if (mid < ql) return query(now->r, mid + 1, r, ql, qr);
    else {
        auto [a, b, c] = query(now->l, l, mid, ql, qr);
        auto [d, e, f] = query(now->r, mid + 1, r, ql, qr);
        return make_tuple(a, b + e - min(c, d), f);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;

        for (int i = 1; i <= n; ++i) cin >> a[i];

        build(root = new node(), 1, n);

        while (m--) {
            int c; cin >> c;
            int l, r; cin >> l >> r;
            if (c == 1) {
                int k; cin >> k;
                modify(root, 1, n, l, r, k);
            } else {
                auto [a, b, c] = query(root, 1, n, l, r);
                cout << b << '\n';
            }
        }
    }
}

