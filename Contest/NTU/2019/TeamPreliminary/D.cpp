#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int p[maxn], e[maxn];

struct treap {
    treap *lc, *rc, *fa;
    int pri, sz, p, e;
    long long psum, mx, tag;
    treap(int p, int e) : fa(nullptr), lc(nullptr), rc(nullptr), p(p), e(e) {
        pri = rand();
        psum = p;
        mx = p + e;
        sz = 1;
        tag = 0;
    }   

    void pull() {
        sz = 1;
        psum = p;
        mx = p + e;
        fa = nullptr;
        if (lc) {
            sz += lc->sz;
            psum += lc->psum;
            mx = max(lc->mx, psum + e);
            lc->fa = this;
        } 
        if (rc) {
            sz += rc->sz;
            mx = max(mx, psum + rc->mx);
            psum += rc->psum;
            rc->fa = this;
        }
    }
};

treap *tr[maxn];

treap *merge(treap *a, treap *b) {
    if (!a || !b) return a ? a : b;
    if (a->pri > b->pri) return a->rc = merge(a->rc, b), a->pull(), a;
    else return b->lc = merge(a, b->lc), b->pull(), b;
}

void split_by_sz(treap *t, int k, treap *&a, treap *&b) {
    if (!t) return a = b = nullptr, void();
    int lsz = 1 + (t->lc ? t->lc->sz : 0);
    if (lsz <= k) a = t, split_by_sz(t->rc, k - lsz, a->rc, b), a->pull();
    else b = t, split_by_sz(t->lc, k, a, b->lc), b->pull();
}

void split_by_val(treap *t, int k, treap *&a, treap *&b) {
    if (!t) return a = b = nullptr, void();
    if (t->e >= k) a = t, split_by_val(t->rc, k, a->rc, b), a->pull();
    else b = t, split_by_val(t->lc, k, a, b->lc), b->pull();
}

int left(treap *t) {
    int res = t->lc ? t->lc->sz : 0;
    while (t->fa) {
        if (t->fa->rc == t) res += 1 + (t->fa->lc ? t->fa->lc->sz : 0);
        t = t->fa;
    }
    return res;
}

void debug(treap *x) {
    if (x->lc) debug(x->lc);
    cout << "(" << x->p << ' ' << x->e << ")" << endl;
    if (x->rc) debug(x->rc);
}

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) scanf("%d", &p[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &e[i]);

    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&](int i, int j) {
        return e[i] > e[j];
    });

    for (int i = 0; i < n; ++i) tr[i] = new treap(p[i], e[i]);

    treap *trp = nullptr;
    for (int i = 0; i < n; ++i) {
        trp = merge(trp, tr[v[i]]);
    }

    printf("%lld\n", trp->mx);

    while (q--) {
        int t, x, y; scanf("%d%d%d", &t, &x, &y); --x;
        int pos = left(tr[x]);
        // printf("pos = %d\n", pos);
        if (t == 1) {
            if (p[x] != y) {
                treap *lp, *rp;
                split_by_sz(trp, pos, lp, rp);
                if (lp) lp->fa = nullptr;
                if (rp) rp->fa = nullptr;
                treap *aa, *bb;
                split_by_sz(rp, 1, aa, bb);
                if (aa) aa->fa = nullptr;
                if (bb) bb->fa = nullptr;
                p[x] = y;
                *tr[x] = treap(p[x], e[x]);
                trp = merge(lp, merge(tr[x], bb));
            }
        } else {
            if (e[x] != y) {
                treap *lp, *rp;
                split_by_sz(trp, pos, lp, rp);
                // cout << "pos = " << pos << endl;
                if (lp) lp->fa = nullptr;
                if (rp) rp->fa = nullptr;
                // if (lp) cout << "lp->sz = " << lp->sz << endl;
                // if (rp) cout << "rp->sz = " << rp->sz << endl;
                treap *aa, *bb;
                split_by_sz(rp, 1, aa, bb);
                if (aa) aa->fa = nullptr;
                if (bb) bb->fa = nullptr;
                trp = merge(lp, bb);
                treap *xx, *yy;
                split_by_val(trp, y, xx, yy);
                if (xx) xx->fa = nullptr;
                if (yy) yy->fa = nullptr;
                e[x] = y;
                *tr[x] = treap(p[x], e[x]);
                trp = merge(xx, merge(tr[x], yy));
            }
        }
        // debug(trp);
        printf("%lld\n", trp->mx);
    }
}
