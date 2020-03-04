#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    int mn, tag;
    node() : l(0), r(0), mn(0), tag(0) {}
    void pull() { mn = min(l->mn, r->mn); }
    void push() { l->addtag(tag), r->addtag(tag); tag = 0; }
    void addtag(int v) { mn += v, tag += v; }
} *root;

int lessme[100005][2];

#define mid ((l + r) >> 1)
void build(node *now, int l, int r) {
    if (l == r) {
        now->mn = lessme[l][0];
        now->tag = 0;
        return;
    }
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
    now->pull();
}

void modify(node *now, int l, int r, int ml, int mr, int v) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        now->addtag(v);
        return;
    }
    now->push();
    modify(now->l, l, mid, ml, mr, v);
    modify(now->r, mid + 1, r, ml, mr, v);
    now->pull();
}

vector<int> op[100005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    int me; cin >> me;
    for (int i = 1; i < n; ++i) {
        int t; cin >> t; if (t < me) ++lessme[0][1];
    }
    for (int i = 1; i <= m; ++i) {
        int t; cin >> t; op[i].resize(t);
        lessme[i][0] = lessme[i - 1][1] - t;
        lessme[i][1] = lessme[i][0];
        for (int j = 0; j < t; ++j) {
            cin >> op[i][j];
            if (op[i][j] < me) ++lessme[i][1];
        }
    }
    build(root = new node(), 1, m);
    while (q--) {
        int x, y, z; cin >> x >> y >> z;
        if (z < me) {
            if (op[x][y - 1] < me);
            else { // ++
                modify(root, 1, m, x + 1, m, 1);
            } 
        } else {
            if (op[x][y - 1] > me);
            else { // --
                modify(root, 1, m, x + 1, m, -1);
            }
        }
        op[x][y - 1] = z;
        cout << (root->mn >= 0) << '\n';
    }
}
