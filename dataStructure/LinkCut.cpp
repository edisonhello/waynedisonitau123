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
    access(a); splay(a); 
    evert(b);
    a->addch(b, 1);
}

void cut(node *a, node *b) {
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
