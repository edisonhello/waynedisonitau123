struct node {
    node *ch[2], *fa, *pfa;
    int sum, v, rev, id;
    node(int s, int id): id(id), v(s), sum(s), rev(0), fa(nullptr), pfa(nullptr) {
        ch[0] = nullptr;
        ch[1] = nullptr;
    }
    int relation() {
        return this == fa->ch[0] ? 0 : 1;
    }
    void push() {
        if (!rev) return;
        swap(ch[0], ch[1]);
        if (ch[0]) ch[0]->rev ^= 1;
        if (ch[1]) ch[1]->rev ^= 1;
        rev = 0;
    }
    void pull() {
        sum = v;
        if (ch[0]) sum += ch[0]->sum;
        if (ch[1]) sum += ch[1]->sum;
    }
    void rotate() {
        if (fa->fa) fa->fa->push();
        fa->push(), push();
        swap(pfa, fa->pfa);
        int d = relation();
        node *t = fa;
        if (t->fa) t->fa->ch[t->relation()] = this;
        fa = t->fa;
        t->ch[d] = ch[d ^ 1];
        if (ch[d ^ 1]) ch[d ^ 1]->fa = t;
        ch[d ^ 1] = t;
        t->fa = this;
        t->pull(), pull();
    }
    void splay() {
        while (fa) {
            if (!fa->fa) {
                rotate();
                continue;
            }
            fa->fa->push(), fa->push();
            if (relation() == fa->relation()) fa->rotate(), rotate();
            else rotate(), rotate();
        }
    }
    void evert() {
        access();
        splay();
        rev ^= 1;
    }
    void expose() {
        splay(), push();
        if (ch[1]) {
            ch[1]->fa = nullptr;
            ch[1]->pfa = this;
            ch[1] = nullptr;
            pull();
        }
    }
    bool splice() {
        splay();
        if (!pfa) return false;
        pfa->expose();
        pfa->ch[1] = this;
        fa = pfa;
        pfa = nullptr;
        fa->pull();
        return true;
    }
    void access() {
        expose();
        while (splice());
    }
    int query() {
        return sum;
    } 
};

namespace lct {
node *sp[maxn];
void make(int u, int v) {
    // create node with id u and value v
    sp[u] = new node(v, u);
}
void link(int u, int v) {
    // u become v's parent
    sp[v]->evert();
    sp[v]->pfa = sp[u];
}
void cut(int u, int v) {
    // u was v's parent
    sp[u]->evert();
    sp[v]->access(), sp[v]->splay(), sp[v]->push();
    sp[v]->ch[0]->fa = nullptr;
    sp[v]->ch[0] = nullptr;
    sp[v]->pull();
}
void modify(int u, int v) {
    sp[u]->splay();
    sp[u]->v = v;
    sp[u]->pull();
}
int query(int u, int v) {
    sp[u]->evert(), sp[v]->access(), sp[v]->splay();
    return sp[v]->query();
}
int find(int u) {
    sp[u]->access();
    sp[u]->splay();
    node *p = sp[u];
    while (true) {
        p->push();
        if (p->ch[0]) p = p->ch[0];
        else break;
    }
    return p->id;
}} 
