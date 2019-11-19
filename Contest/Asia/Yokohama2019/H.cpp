#include <bits/stdc++.h>
using namespace std;

struct Treap {
    struct node {
        node *l, *r;
        int pri, val, sz, pos, tag;
        node(int v = 0, int p = 0) : l(0), r(0), pri(rand()), val(v), sz(1), pos(p), tag(0) {}
        void addtag(int v) { val += v, tag += v; }
        void push() { if (l) l->addtag(tag); if (r) r->addtag(tag); tag = 0; }
        int lz() { return l ? l->sz : 0; }
        int rz() { return r ? r->sz : 0; }
        void pull() { sz = 1 + lz() + rz(); }
    } *root;
    Treap() : root(0) {}
    void dfs(node *now) {
        if (!now) return;
        now->push();
        if (now->l) cout << "{", dfs(now->l), cout << "}";
        cout << "(val " << now->val << ", pos " << now->pos << ", tag " << now->tag << ")";
        if (now->r) cout << "{", dfs(now->r), cout << "}";
    }
    void print(node *p) {
        return;
        cout << "[";
        dfs(p);
        cout << "]" << endl;
    }
    node *merge(node *a, node *b) {
        if (!b) return a;
        if (!a) return b;
        if (a->pri > b->pri) {
            a->push();
            a->r = merge(a->r, b);
            a->pull();
            return a;
        } else {
            b->push();
            b->l = merge(a, b->l);
            b->pull();
            return b;
        }
    }
    void merge(node *a, node *b, node *c) {
        root = merge(a, merge(b, c));
    }
    void split_val_pos(node *now, int v, int p, node *&a, node *&b) {
        if (!now) return a = b = 0, void();
        now->push();
        if (now->val < v || (now->val == v && now->pos <= p)) {
            a = now;
            split_val_pos(now->r, v, p, a->r, b);
            a->pull();
        } else {
            b = now;
            split_val_pos(now->l, v, p, a, b->l);
            b->pull();
        }
    }
    void split_zero(node *&a, node *&b, node *&c) {
        node *tmp;
        split_val_pos(root, -1, 1e9, a, tmp);
        split_val_pos(tmp, 0, 1e9, b, c);
    }
    void addnode(int of, int pz) {
        // cerr << "addnode: " << of << " " << pz << endl;
        node *a, *b;
        split_val_pos(root, 0, pz - 1, a, b);
        // cerr << "a = "; print(a);
        root = merge(a, merge(new node(0, pz), b));
        root->addtag(of);
        print(root);
    }
    void delnode(int of, int pz) {
        node *a, *b, *c, *t;
        root->addtag(-of);
        split_val_pos(root, 0, pz - 1, a, t);
        split_val_pos(t, 0, pz, b, c);
        assert(b);
        delete b;
        root = merge(a, c);
    }
} treap;

struct Segtree {
    static const int maxn = 200005;
    struct node {
        node *l, *r;
        int val, mx, tag;
        node(int v = 0) : l(0), r(0), val(v), mx(v), tag(0) {}
        void addtag(int z) { val += z, mx += z, tag += z; }
        void pull() { mx = max(l->mx, r->mx); }
        void push() { if (tag) { l->addtag(tag), r->addtag(tag), tag = 0; } }
    } *root;
#define mid ((l + r) >> 1)
    Segtree() { build(root = new node(), 1, maxn); }
    void build(node *now, int l, int r) {
        if (l == r) return;
        build(now->l = new node(), l, mid);
        build(now->r = new node(), mid + 1, r);
    }
    void modify(int l, int r, int v) { modify(root, 1, maxn, l, r, v); }
    void modify(node *now, int l, int r, int ml, int mr, int v) {
        if (mr < l || r < ml) return;
        if (ml <= l && r <= mr) {
            now->addtag(v);
            return;
        }
        now->push();
        modify(now->l, l, mid, ml, mr, v);
        modify(now->r, mid + 1, r, ml, mr, v);
        now->pull();
    }
    int query_max(int l) { return query_max(root, 1, maxn, l, maxn); }
    int query_max(node *now, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return -1e9;
        if (ql <= l && r <= qr) return now->mx;
        now->push();
        return max(query_max(now->l, l, mid, ql, qr), query_max(now->r, mid + 1, r, ql, qr));
    }
#undef mid
} seg;

int main() {
    string s; cin >> s;
    stack<int> rec;
    string str;
    long long ans = 0;
    for (char c : s) {
        if (c == '(') {
            str += c;
            treap.addnode(1, str.size());
            seg.modify(1, str.size(), 1);
            rec.push(0);
        } else if (c == ')') {
            str += c;
            treap.addnode(-1, str.size());
            seg.modify(1, str.size(), -1);

            Treap::node *a, *b, *c;
            treap.split_zero(a, b, c);
            int thisadd = 0;
            function<void(Treap::node *)> Dfs = [&] (Treap::node *now) {
                if (!now) return;
                if (seg.query_max(now->pos) <= 0) {
                    thisadd += now->rz() + 1;
                    Dfs(now->l);
                } else {
                    Dfs(now->r);
                }
            };
            Dfs(b);
            treap.merge(a, b, c);
            ans += thisadd;
            rec.push(thisadd);
        } else {
            ans -= rec.top();
            if (str.back() == '(') {
                treap.delnode(1, str.size());
                seg.modify(1, str.size(), -1);
            }
            else {
                treap.delnode(-1, str.size());
                seg.modify(1, str.size(), 1);
            }
            rec.pop();
            str.pop_back();
        }
        cout << ans << '\n';
    }
}
