#include <bits/stdc++.h>
using namespace std;

struct treap {
    treap *lc, *rc;
    int sz, pri, a, b, nxt, add, tag;
    treap(int a, int b): 
        a(a), b(b), lc(nullptr), rc(nullptr), sz(1), pri(rand()) {}
};

treap *merge(treap *a, treap *b) {
    if (!a || !b)
        return a ? a : b;
    if (a->pri > b->pri)
        return a->rc = merge(a->rc, b), a->pull(), a;
    else
        return b->lc = merge(a, b->lc), b->pull(), b;
}

void split(treap *t, int k, treap *&a, treap *&b) {
    if (!t)
        return a = b = nullptr, void();

    int lsz = (t->lc ? t->lc->sz : 0) + 1;
    if (lsz <= k)
        a = t, split(t->rc, k - lsz, a->rc, b), a->pull();
    else
        b = t, split(t->lc, k, a, b->lc), b->pull();
}

int main() {
    int q; scanf("%d", &q);
    while (q--) {
        int t, k; scanf("%d%d", &t, &k);
        if (t == 1) {
            int a, b; scanf("%d%d", &a, &b);
        }    
        if (t == 2) {

        }
        if (t == 3) {

        }
    }
    return 0;
}
