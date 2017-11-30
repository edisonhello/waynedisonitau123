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
