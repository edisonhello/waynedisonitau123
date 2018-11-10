#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const int inf = 1e9;
int s[maxn], a[maxn], n;

struct treap {
    treap *lc, *rc;
    int val, pri, sz;
    treap(int v): val(v), pri(rand()), sz(1), lc(nullptr), rc(nullptr) {}
    void pull() {
        sz = 1;
        if (lc) sz += lc->sz;
        if (rc) sz += rc->sz;
    }
};

treap *merge(treap *a, treap *b) {
    if (!a || !b) return a ? a : b;
    if (a->pri > b->pri) return a->rc = merge(a->rc, b), a->pull(), a;
    else return b->lc = merge(a, b->lc), b->pull(), b;
}

void split(treap *t, int k, treap *&a, treap *&b) {
    if (!t) return a = b = nullptr, void();
    int lsz = (t->lc ? t->lc->sz : 0) + 1;
    if (lsz <= k) a = t, split(t->rc, k - lsz, a->rc, b), a->pull();
    else b = t, split(t->lc, k, a, b->lc), b->pull();
}

void split2(treap *t, int k, treap *&a, treap *&b) {
    if (!t) return a = b = nullptr, void();
    if (t->val <= k) a = t, split2(t->rc, k, a->rc, b), a->pull();
    else b = t, split2(t->lc, k, a, b->lc), b->pull();
}

void insert(treap *&t, int x) {
    treap *a, *b;
    split2(t, x - 1, a, b);
    t = merge(merge(a, new treap(x)), b);
}

void erase(treap *&t, int x) {
    treap *a, *b;
    split2(t, x - 1, a, b);
    treap *c, *d;
    split2(b, x, c, d);
    t = merge(a, merge(merge(c->lc, c->rc), d));
}

int win(treap *t, int x) {
    treap *a, *b;
    split2(t, x, a, b);
    int res = (b ? b->sz : 0);
    t = merge(a, b);
    return res;
}

int lose(treap *t, int x) {
    treap *a, *b;
    split2(t, x - 1, a, b);
    int res = (a ? a->sz : 0);
    t = merge(a, b);
    return res;
}

void del(treap *t) {
    if (!t) return;
    del(t->lc);
    del(t->rc);
    delete t;
}

bool check(int x) {
    // printf("check x = %d\n", x);
    treap *t = nullptr;
    for (int i = 0; i < n; ++i) a[i] = s[i];
    a[0] += x;
    for (int i = 0; i < n; ++i) insert(t, a[i]);
    // puts("hey");
    for (int i = 0; i < n; ++i) {
        int w = win(t, a[i]), l = lose(t, a[i]);
        erase(t, a[i]);
        a[i] += l - w;
        insert(t, a[i]);
    }
    del(t);
    for (int i = 1; i < n - 1; ++i) {
        if (a[0] <= a[i]) return false;
    }
    return true;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &s[i]);
        s[n - 1] = inf;
        int d = 31, ans = 1e9;
        while (d--) {
            int x = ans - (1 << d);
            if (x < 0) continue;
            if (check(x)) ans = x;
        }
        printf("%d\n", ans);
    }
    return 0;
}
