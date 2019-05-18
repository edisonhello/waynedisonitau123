#pragma GCC optimize("O3", "no-stack-protector")
// #pragma GCC target("avx")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

struct treap {
    treap *lc, *rc, *fa;
    int sz, val;
    treap(int v = 0): sz(1), val(v), lc(nullptr), rc(nullptr), fa(nullptr) {}
    int lz() { return lc ? lc->sz : 0; } 
    int rz() { return rc ? rc->sz : 0; } 
    void pull() {
        sz = 1;
        if (lc) {
            sz += lc->sz;
            lc->fa = this;
        }
        if (rc) {
            sz += rc->sz;
            rc->fa = this;
        }
        fa = nullptr;
    }
};

const int maxn = 4e5 + 7;
treap *group[maxn];
treap *fr[maxn];
treap *tr[maxn];
treap pool[maxn * 2];

treap *get_treap(int v) {
    static int ptr = 0;
    pool[ptr].val = v;
    return &pool[ptr++];
}

void insert_tr(treap *&t, int le, int nw) {
    // cout << t << " " << le << endl;
    if (!t) {
        tr[nw] = t = get_treap(nw);
    } else if (t->lz() >= le) {
        insert_tr(t->lc, le, nw);
        t->pull();
        if (t->lz() * 1 > t->rz() * 2) {
            treap *tmp = t->lc;
            t->lc = tmp->rc;
            tmp->rc = t;
            t = tmp;
            t->rc->pull();
            t->pull();
        }
    } else {
        insert_tr(t->rc, le - t->lz() - 1, nw);
        t->pull();
        if (t->rz() * 1 > t->lz() * 2) {
            treap *tmp = t->rc;
            t->rc = tmp->lc;
            tmp->lc = t;
            t = tmp;
            t->lc->pull();
            t->pull();
        }
    }
}

void insert_fr(treap *&t, int le, int nw) {
    // cout << t << " " << le << endl;
    if (!t) {
        fr[nw] = t = get_treap(nw);
    } else if (t->lz() >= le) {
        insert_fr(t->lc, le, nw);
        t->pull();
        if (t->lz() * 1 > t->rz() * 2) {
            treap *tmp = t->lc;
            t->lc = tmp->rc;
            tmp->rc = t;
            t = tmp;
            t->rc->pull();
            t->pull();
        }
    } else {
        insert_fr(t->rc, le - t->lz() - 1, nw);
        t->pull();
        if (t->rz() * 1 > t->lz() * 2) {
            treap *tmp = t->rc;
            t->rc = tmp->lc;
            tmp->lc = t;
            t = tmp;
            t->lc->pull();
            t->pull();
        }
    }
}

inline char gtx() {
    const int N = 4096;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        end = buf + fread(buf, 1, N, stdin);
        p = buf;
    }
    return *p++;
}

#define getchar gtx
inline void rit(int &x) {
    char c = 0;
    while (c = gtx(), !isdigit(c));
    x = c & 15;
    while (c = gtx(), isdigit(c)) x = x * 10 + (c & 15);
}


int find_real_position(int v) {
    treap *ptr = tr[v];
    int res = ptr->lc ? ptr->lc->sz : 0;
    while (ptr->fa) {
        if (ptr == ptr->fa->rc)
            res += (ptr->fa->lc ? ptr->fa->lc->sz : 0) + 1;
        ptr = ptr->fa;
    }
    return res;
}

int find_position(int c, int i, int a) {
    treap *ptr = group[c];
    int ps = i;
    while (ptr) {
        int p = find_real_position(ptr->val);
        if (p >= i - a) ps = min(ps, p);
        if (p + 1 >= i - a) ps = min(ps, p + 1);
        if (p >= i - a) 
            ptr = ptr->lc;
        else
            ptr = ptr->rc;
    }
    /* if (ps == i - a)
        return ps + 1;
    return ps; */
    return ps;
}

int find_less(int c, int a) {
    treap *ptr = group[c];
    int res = 0;
    while (ptr) {
        int p = find_real_position(ptr->val);
        if (p >= a) {
            ptr = ptr->lc;
        } else {
            res += (ptr->lc ? ptr->lc->sz : 0) + 1;
            ptr = ptr->rc;
        }
    }
    return res;
}

int ans[maxn];

void dfs(treap *t) {
    if (!t) return;
    dfs(t->lc);
    cout << "(" << t->val << ", " << find_real_position(t->val) << ")" << ' ';
    dfs(t->rc);
}

void debug() {
    for (int i = 0; i < 3; ++i) {
        dfs(group[i]);
        cout << endl;
    }
}



char buf[1 << 22];
char *ptr = buf;
char stk[10];
char *p = stk;
void print(int x) {
    while (x) {
        *p++ = x % 10 + '0';
        x /= 10;
    }
    while (p != stk)
        *ptr++ = *--p;
    *ptr++ = ' ';
}

int main() {
    // srand(7122);
    int n; // scanf("%d", &n);
    rit(n);
    treap *f = nullptr;
    for (int i = 0; i < n; ++i) {
        int c, a; // scanf("%d%d", &c, &a); --c;
        rit(c); rit(a); --c;
        int p = find_position(c, i, a);
        // printf("p = %d\n", p);
        // treap *l, *r;
        /* split(f, p, l, r);
        f = merge(merge(l, tr[i]), r); */
        // tr[i] = get_treap(i);
        insert_tr(f, p, i);
        int le = find_less(c, p);        
        // printf("le = %d\n", le);
        /* split(group[c], le, l, r);
        group[c] = merge(merge(l, fr[i]), r); */
        // fr[i] = get_treap(i);
        insert_fr(group[c], le, i);

        // debug();
    }
    for (int i = 0; i < n; ++i) 
        ans[find_real_position(i)] = i;
    for (int i = 0; i < n; ++i) print(ans[i] + 1);
    fwrite(buf, 1, ptr - buf, stdout);
    return 0;
}
