#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    long long tag, mn;
    node() : l(0), r(0), tag(0), mn(0) {}
    void addtag(long long x) {
        tag += x;
        mn += x;
    }
    void push() {
        if (tag) {
            l->addtag(tag);
            r->addtag(tag);
            tag = 0;
        }
    }
    void pull() {
        mn = min(l->mn, r->mn);
    }
} *root, pool[500005 * 4];
int ptr;

int a[500005];
int b[500005];
long long prea[500005];

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) {
        now->mn = -prea[l];
        // cerr << "pos " << l << " init " << -prea[l] << endl;
        return;
    }
    build(now->l = &pool[ptr++], l, mid);
    build(now->r = &pool[ptr++], mid + 1, r);
    now->pull();
}

void modify(node *now, int l, int r, int ml, int mr, long long x) {
    if (mr < l || r < ml) return;
    if (ml <= l && r <= mr) {
        now->addtag(x);
        return;
    }
    now->push();
    modify(now->l, l, mid, ml, mr, x);
    modify(now->r, mid + 1, r, ml, mr, x);
    now->pull();
}

int bit[500005];
void add(int x, int v) {
    ++x;
    for (; x < 500005; x += x & -x) {
        bit[x] += v;
    }
}
int query(int x) {
    ++x;
    int v = 0;
    for (; x; x -= x & -x) {
        v += bit[x];
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    int k = 500000;

    vector<int> o(n); iota(o.begin(), o.end(), 1);
    sort(o.begin(), o.end(), [&] (int x, int y) -> bool { return a[x] > a[y]; });
    for (int i = 1; i <= n; ++i) prea[i] = prea[i - 1] + a[o[i - 1]];
    for (int i = n + 1; i <= k; ++i) prea[i] = prea[i - 1];
    for (int i = 1; i <= n; ++i) add(a[i], 1);

    // int k = max(n, m);
    build(root = &pool[ptr++], 1, k);

    priority_queue<int> allb;
    long long bsum = 0;
    for (int i = 1; i <= m; ++i) allb.push(b[i]), bsum += b[i];
    int cc = 0;
    for (int kk = k; kk >= 1; --kk) {
        while (allb.size() && allb.top() >= kk) {
            bsum -= allb.top();
            allb.pop();
            ++cc;
        }
        // cerr << "modify " << kk << " " << bsum << endl;
        modify(root, 1, k, kk, kk, bsum + 1ll * cc * kk);
    }

    int q; cin >> q; while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            int ord = query(k) - query(a[x]);
            // cerr << "modify " << ord + 1 << " to " << k << " all " << -1 << endl;
            modify(root, 1, k, ord + 1, k, -1);
            add(a[x], -1);
            ++a[x];
            add(a[x], 1);

        } else if (t == 2) {
            int ord = query(k) - query(a[x] - 1);
            // cerr << "modify " << ord << " to " << k << " all " << 1 << endl;
            modify(root, 1, k, ord, k, 1);
            add(a[x], -1);
            --a[x];
            add(a[x], 1);

        } else if (t == 3) {
            // cerr << "modify " << b[x] + 1 << " to " << k << " all " << 1 << endl;
            modify(root, 1, k, b[x] + 1, k, 1);
            ++b[x];
        } else {
            // cerr << "modify " << b[x] << " to " << k << " all " << -1 << endl;
            modify(root, 1, k, b[x], k, -1);
            --b[x];
        }

        if (root->mn >= 0) cout << "1\n";
        else cout << "0\n";
    }
}

