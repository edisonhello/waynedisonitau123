#include <bits/stdc++.h>
using namespace std;

/* struct node {
    node *l, *r;
    int pri, val, sz;
    int lz() { return l ? l->sz : 0; }
    int rz() { return r ? r->sz : 0; }
    void pull() { sz = lz() + rz() + 1; }
    node(int v) : l(0), r(0), pri(rand()), val(v), sz(1) {}
} *root;

node *merge(node *a, node *b) {
    if (!a) return b;
    if (!b) return a;
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

void split_sz(node *now, int sz, node *&a, node *&b) {
    if (!now) { a = b = 0; return; }
    if (now->lz() >= sz) {
        b = now;
        split_sz(now->l, sz, a, b->l);
    } else {
        a = now;
        split_sz(now->r, sz - now->lz() - 1, a->r, b);
    }
    now->pull();
}

void split_val(node *now, int val, node *&a, node *&b) {
    if (!now) { a = b = 0; return; }
    if (now->val > val) {
        b = now;
        split_val(now->l, val, a, b->l);
    } else {
        a = now;
        split_val(now->r, val, a->r, b);
    }
    now->pull();
}

void remove(int v) {
    // cerr << "remove " << v << endl;
    node *a, *b, *c, *d;
    split_val(root, v - 1, a, d);
    split_sz(d, 1, b, c);
    delete b;
    root = merge(a, c);
}

void insert(int v) {
    // cerr << "insert " << v << endl;
    node *a, *b;
    split_val(root, v, a, b);
    root = merge(merge(a, new node(v)), b);
}

int query(int k) {
    if (!root) return -1;
    if (root->sz < k) return -1;
    node *a, *b, *c, *d;
    split_sz(root, k - 1, a, d);
    split_sz(d, 1, b, c);
    int val = b->val;
    root = merge(merge(a, b), c);
    return val;
}

void print(node *now) {
    if (!now) return;
    if (now->l) cerr << "[", print(now->l), cerr << "]";
    cerr << now->val;
    if (now->r) cerr << "[", print(now->r), cerr << "]";
}

void clear(node *&now) {
    if (!now) return;
    clear(now->l);
    clear(now->r);
    delete now;
    now = 0;
} */

#define getchar gtx
inline int gtx() {
    static const int N = 4096;
    static char b[N];
    static char *p = b, *e = b;
    if (p == e) {
        e = b + fread(b, 1, N, stdin);
        p = b;
    }
    return *p++;
}

inline void rit(int &x) {
    char c = 0;
    while (c = gtx(), (c < '0') || c > '9');
    x = c & 15;
    while (c = gtx(), c >= '0' && c <= '9') x = x * 10 + (c & 15);
}

const int L = 20;
const int maxn = 1 << L;
int fw[maxn];

void remove(int v) {
    for (int i = v; i < maxn; i += i & -i) fw[i] -= 1;
}

void insert(int v) {
    for (int i = v; i < maxn; i += i & -i) fw[i] += 1;
}

int query(int k) {
    int z = k - 1, v = 0;
    for (int i = L - 1; i >= 0; --i) {
        if (fw[v | (1 << i)] <= z) {
            z -= fw[v | (1 << i)];
            v |= (1 << i);
        }
    }
    if (v == maxn - 1) return -1;
    return v + 1;
}

int main() {
    int t; rit(t); for (int ts = 1; ts <= t; ++ts) {
        // clear(root);
        printf("Case %d:\n", ts);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int q; rit(q); while (q--) {
            int o; rit(o);
            int s; rit(s);
            while (pq.size() && pq.top().first < s) {
                remove(pq.top().second);
                pq.pop();
            }
            if (o == 1) {
                int v, t; rit(v); rit(t);
                insert(v);
                pq.emplace(t, v);
            } else if (o == 2) {
                int k; rit(k);
                printf("%d\n", query(k));
            }
            // cerr << "tree = ";
            // print(root);
            // cerr << endl;
        }
        while (!pq.empty()) remove(pq.top().second), pq.pop();
    }
}
