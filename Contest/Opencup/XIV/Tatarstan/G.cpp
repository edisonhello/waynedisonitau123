#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    int mx, tag;
    node() : l(0), r(0), mx(0), tag(0) {}
    void add(int x) {
        mx += x;
        tag += x;
    }
    void push() {
        if (tag) {
            l->add(tag);
            r->add(tag);
            tag = 0;
        }
    }
    void pull() {
        mx = max(l->mx, r->mx);
    }
};
node pool[100005 * 4];
int poolptr;

struct segtree {
    node *root;
    int R;
    segtree() : root(0), R(0) {}
#define mid ((l + r) >> 1)
    void build(node *now, int l, int r) {
        if (l == r) return;
        build(now->l = &pool[poolptr++], l, mid);
        build(now->r = &pool[poolptr++], mid + 1, r);
    }
    void build(int sz) {
        R = sz;
        build(root = &pool[poolptr++], 1, R);
    }
    void modify(node *now, int l, int r, int ml, int mr) {
        if (mr < l || r < ml) return;
        if (ml <= l && r <= mr) return now->add(1), void();
        now->push();
        modify(now->l, l, mid, ml, mr);
        modify(now->r, mid + 1, r, ml, mr);
        now->pull();
    }
    void add(int x) {
        modify(root, 1, R, 1, x);
    }
    bool is_empty() {
        return !root->mx;
    }
    int find_one(node *now, int l, int r, int R) {
        if (l == r) return l;
        now->push();
        if (now->r->mx && mid + 1 <= R) return find_one(now->r, mid + 1, r, R);
        else return find_one(now->l, l, mid, R);
    }
    int find_one(int r) {
        return find_one(root, 1, R, r);
    }
};


vector<int> G[100005];
int pa[100005], dep[100005], mxch[100005];
int bel[100005], cpos[100005], cpa[100005], cc;
vector<int> mem[100005];
segtree seg[100005];

void dfs(int now, int p) {
    mxch[now] = now;
    pa[now] = p;
    for (int i : G[now]) if (i != p) {
        dep[i] = dep[now] + 1;
        dfs(i, now);
        if (dep[mxch[i]] > dep[mxch[now]]) mxch[now] = mxch[i];
    }
}
void dfs1(int now, int ncc, int cp) {
    // cerr << "dfs1 " << now << " " << ncc << " " << cp << endl;
    bel[now] = ncc;
    cpos[now] = cp;
    mem[ncc].push_back(now);
    for (int i : G[now]) if (i != pa[now]) {
        if (mxch[i] == mxch[now]) dfs1(i, ncc, cp + 1);
        else {
            ++cc;
            cpa[cc] = now;
            dfs1(i, cc, 1);
        }
    }
}

int pos[100005];

void add(int now) {
    while (now) {
        // cerr << "seg id " << bel[now] << " add from " << cpos[now] << endl;
        seg[bel[now]].add(cpos[now]);
        now = cpa[bel[now]];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    dfs1(1, ++cc, 1);
    for (int i = 1; i <= cc; ++i) seg[i].build((int)mem[i].size());
    add(1);
    int m; cin >> m;
    for (int i = 1; i <= m; ++i) cin >> pos[i];
    int cur = 0;
    for (int i = 1; i <= m; ++i) {
        int x = pos[i];
        while (seg[bel[x]].is_empty()) x = cpa[bel[x]];
        x = mem[bel[x]][seg[bel[x]].find_one(cpos[x]) - 1];
        // cerr << "find x = " << x << endl;
        cur += 2 * (dep[pos[i]] - dep[x]);
        cout << cur - dep[pos[i]] << ' ';
        add(pos[i]);
    }
    cout << endl;
}
