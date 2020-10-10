#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

struct node {
    node *l, *r;
    int sum, sz;
    int tag, ttag;
    node() : l(0), r(0), sum(0), sz(1), tag(-1), ttag(-1) {}
    void set(int x) {
        sum = x * 1ll * sz % mod;
        tag = x;
        ttag = 1;
    }
    void mul(int x) {
        sum = 1ll * sum * x % mod;
        if (tag != -1) {
            tag = 1ll * tag * x % mod;
        } else {
            ttag = ttag * 1ll * x % mod;
        }
    }
    void pull() {
        sum = (l->sum + r->sum);
        if (sum >= mod) sum -= mod;
    }
    void push() {
        if (tag != -1) {
            if (l) l->set(tag);
            if (r) r->set(tag);
            tag = -1;
        } else {
            if (l) l->mul(ttag);
            if (r) r->mul(ttag);
            ttag = 1;
        }
    }
} *root;

int pw(int b, int n, int m) {
    int a = 1;
    while (n) {
        if (n & 1) a = 1ll * a * b % m;
        b = 1ll * b * b % m; n >>= 1;
    }
    return a;
}

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) return;
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
    now->sz = now->l->sz + now->r->sz;
}

void Set(node *now, int l, int r, int ml, int mr, int x) {
    if (r < ml || mr < l) return;
    now->push();
    if (ml <= l && r <= mr) {
        now->set(x);
        return;
    }
    Set(now->l, l, mid, ml, mr, x);
    Set(now->r, mid + 1, r, ml, mr, x);
    now->pull();
}

void mul(node *now, int l, int r, int ml, int mr, int x) {
    if (r < ml || mr < l) return;
    now->push();
    if (ml <= l && r <= mr) {
        now->mul(x);
        return;
    }
    mul(now->l, l, mid, ml, mr, x);
    mul(now->r, mid + 1, r, ml, mr, x);
    now->pull();
}

int query(node *now, int l, int r, int ql, int qr) {
    if (r < ql || qr < l) return 0;
    now->push();
    if (ql <= l && r <= qr) {
        return now->sum;
    }
    int s = query(now->l, l, mid, ql, qr) + query(now->r, mid + 1, r, ql, qr);
    if (s >= mod) s -= mod;
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;

    build(root = new node(), 1, n);

    int ans = 0;

    while (q--) {
        int l, r;
        char c;
        int x; 
        cin >> l >> r >> c >> x;
        if (c == '-') {
            x = mod - x;
            c = '+';
        } 
        if (c == '/') {
            x = pw(x, mod - 2, mod);
            c = '*';
        }

        if (c == '+') {
            ans += query(root, 1, n, l, r);
            if (ans >= mod) ans -= mod;

            Set(root, 1, n, l, r, x);
        } else {
            mul(root, 1, n, l, r, x);
        }
    }

    ans += query(root, 1, n, 1, n);
    cout << ans % mod << endl;
}
