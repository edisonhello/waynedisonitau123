#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    int sz, pri, val, cnt9, right;
    void pull() {
        sz = lz() + rz() + 1;
        if (l) {
            if (l->cnt9 == l->sz) {
                if (cnt9) {
                    cnt9 = l->cnt9 + 1 + (r ? r->cnt9 : 0);
                    right = (r ? r->right : val);
                } else {
                    cnt9 = l->cnt9;
                    right = val;
                }
            } else {
                cnt9 = l->cnt9;
                right = l->right;
            }
        } else {
            if (cnt9) {
                cnt9 = 1 + (r ? r->cnt9 : 0);
                right = (r ? r->right : val);
            } else {
                cnt9 = l->cnt9;
                right = val;
            }
        }
    }
    int lz() { return l ? l->sz : 0; }
    int rz() { return r ? r->sz : 0; }
    node(int v) : l(0), r(0), sz(1), pri(rand()), val(v), cnt9(v >= 9), right(10) {}
} *root;

node *merge(node *a, node *b) {
    if (a->pri > b->pri) {
        a->r = merge(a->r, b);
        a->pull();
        return a;
    } else {
        b->l = merge(a, b->l);
        b->pull();
        return b;
    }
}

void split(node *now, int lz, node *&a, node *&b) {
    if (!now) { a = b = 0; return; }
    if (now->lz() >= lz) {
        b = now;
        split(now->l, lz, a, b->l);
        b->pull();
    } else {
        a = now;
        split(now->r, lz - now->lz() - 1, a->r, b);
        a->pull();
    }
}

int dfs(node *now, int lz) {
    if (now->lz() > lz) {
        dfs(now->l, lz);
    }
}

int main() {
    root = new node(10);
    root->cnt9 = 0;
    int q; scanf("%d", &q);
    while (q--) {
        int t, k; scanf("%d%d", &t, &k);
        if (t == 1) {
            int a, b; scanf("%d%d", &a, &b);
            node *l, *r; split(root, k, l, r);
            root = merge(merge(l, new node(a + b)), r);
        }    
        if (t == 2) {
            node *l, *r; split(root, k - 1, l, r);
            node *x, *y; split(r, 1, x, y);
            delete x;
            root = merge(l, y);
        }
        if (t == 3) {
            printf("%d\n", dfs(root, k));
        }
    }
}
