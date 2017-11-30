#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;

struct node {
    static node nil;
    node *ch[2], *fa;
    int val, sz, tag;
    node(): sz(0), tag(0), val(-1) { fa = ch[0] = ch[1] = &nil; }
    node(int v): val(v), sz(1), tag(0) { fa = ch[0] = ch[1] = &nil; }
    bool r() { return fa->ch[0] != this && fa->ch[1] != this; }
    int dir() { return fa->ch[0] == this ? 0 : 1; }
    void pull() {
        sz = ch[0]->sz + ch[1]->sz + 1;
        if (ch[0] != &nil) ch[0]->fa = this;
        if (ch[1] != &nil) ch[1]->fa = this;
    }
    void push() {
        if (tag == 0) return;
        swap(ch[0], ch[1]);
        if (ch[0] != &nil) ch[0]->tag ^= 1;
        if (ch[1] != &nil) ch[1]->tag ^= 1;
        tag = 0;
    }
    void addch(node *c, int d) {
        ch[d] = c;
        if (c != &nil) c->fa = this;
        pull();
    }
} node::nil;

node *nil = &node::nil;

void rotate(node *s) {
    node *p = s->fa;
    int d = s->dir();
    if (!p->r()) p->fa->addch(s, p->dir());
    else s->fa = p->fa;
    p->addch(s->ch[d ^ 1], d);
    s->addch(p, d ^ 1);
    p->pull(); s->pull();
}

void splay(node *s) {
    vector<node*> vec;
    for (node *n = s; ; n = n->fa) {
        vec.push_back(n);
        if (n->r()) break;
    }
    reverse(vec.begin(), vec.end());
    for (auto it : vec) it->push();
    while (!s->r()) {
        if (s->fa->r()) rotate(s);
        else if (s->dir() == s->fa->dir()) rotate(s->fa), rotate(s);
        else rotate(s), rotate(s);
    }
}

node *access(node *s) {
    node *n = nil;
    for (; s != nil; s = s->fa) {
        splay(s);
        s->addch(n, 1);
        n = s;
    }
    return n;
}

void evert(node *s) {
    access(s); splay(s);
    s->tag ^= 1;
    s->push(); s->pull();
}

void link(node *a, node *b) {
    cout << "link" << endl;
    access(a); splay(a); 
    evert(b);
    a->addch(b, 1);
}

void cut(node *a, node *b) {
    cout << "cut" << endl;
    access(b); splay(b); 
    b->push();
    b->ch[0] = b->ch[0]->fa = nil;
}

node *find(node *s) {
    s = access(s);
    while (s->ch[0] != nil) s = s->ch[0];
    splay(s);
    return s;
}

int query(node *a, node *b) {
    access(a); access(b);
    splay(a);
    int ret = a->fa->val;
    if (ret == -1) ret = a->val;
    return ret;
}

node *p[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) p[i] = new node(i);
    int ans = n;
    while (q--) {
        char c; int a, b; cin >> c;
        if (c == '+' || c == '-') cin >> a >> b;
        else { cout << ans << endl; continue; }
        if (a > b) swap(a, b);
        node *pa = find(p[a]), *pb = find(p[b]);
        if (pa != pb && c == '+') --ans;
        if (c == '+') link(p[a], p[b]);
        if (c == '-') cut(p[a], p[b]);
        node *ppa = find(p[a]), *ppb = find(p[b]);
        if (pa == pb && ppa != ppb) ++ans;
        cout << "b" << endl;
    }
    return 0;
}
