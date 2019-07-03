#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e6 + 5;
vector<int> g[maxn];
int n, q, a[maxn], b[maxn], fa[maxn], dep[maxn], sz[maxn], to[maxn], fr[maxn], tin[maxn], tout[maxn], tk;
 
pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.first == b.first)
        return make_pair(a.first, a.second + b.second);
    if (a.second > b.second)
        return make_pair(a.first, a.second - b.second);
    else
        return make_pair(b.first, b.second - a.second);
}
 
pair<int, int> st[maxn * 4];
 
void dfs(int x, int p) {
    sz[x] = 1;
    to[x] = -1;
    fa[x] = p;
    dep[x] = ~p ? dep[p] + 1 : 0;
 
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
        if (to[x] == -1 || sz[u] > sz[to[x]])
            to[x] = u;
    }
}
 
void link(int x, int f) {
    fr[x] = f;
    tin[x] = tk++;
    if (to[x] != -1) link(to[x], f);
    
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == fa[x]) continue;
        if (u == to[x]) continue;
        link(u, u);
    }
    tout[x] = tk;
}
 
void build(int l, int r, int o = 0) {
    if (r - l == 1)
        return st[o] = make_pair(b[l], 1), void();
 
    build(l, (l + r) >> 1, o * 2 + 1);
    build((l + r) >> 1, r, o * 2 + 2);
    st[o] = st[o * 2 + 1] + st[o * 2 + 2];
}
 
pair<int, int> query(int l, int r, int ql, int qr, int o = 0) {
    // printf("query l = %d r = %d ql = %d qr = %d\n", ql, qr);
    if (l >= ql && r <= qr)
        return st[o];
 
    int m = (l + r) >> 1;
    if (qr <= m)
        return query(l, m, ql, qr, o * 2 + 1);
    if (ql >= m)
        return query(m, r, ql, qr, o * 2 + 2);
 
    return query(l, m, ql, qr, o * 2 + 1) + query(m, r, ql, qr, o * 2 + 2);
}
 
vector<pair<int, int>> qpath(int u, int v, int &lca) {
    int fu = fr[u], fv = fr[v];
    vector<pair<int, int>> res;
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(u, v);
            swap(fu, fv);
        }
 
        res.emplace_back(tin[fu], tin[u] + 1);
        u = fa[fu];
        fu = fr[u];
    }
 
    if (tin[u] > tin[v]) swap(u, v);
    lca = u;
    res.emplace_back(tin[u], tin[v] + 1);
    return res;
}
 
pair<int, int> candidate(const vector<pair<int, int>> &path) {
    pair<int, int> res = query(0, n, path[0].first, path[0].second);
    for (int i = 1; i < (int)path.size(); ++i)
        res = res + query(0, n, path[i].first, path[i].second);
    return res;
}
 
namespace pst {
    const int maxc = 6e7;
    int st[maxc], lc[maxc], rc[maxc];
 
    void init() {
        memset(lc, -1, sizeof(lc));
        memset(rc, -1, sizeof(rc));
    }
 
    int gnode() {
        static int sz = 0;
        st[sz] = 0;
        return sz++;
    }
 
    void modify(int l, int r, int p, int o) {
        if (r - l == 1)
            return st[o]++, void();
 
        if (p < (l + r) >> 1) {
            if (lc[o] == -1) lc[o] = gnode();
            modify(l, (l + r) >> 1, p, lc[o]);
        } else {
            if (rc[o] == -1) rc[o] = gnode();
            modify((l + r) >> 1, r, p, rc[o]);
        }
 
        st[o] = (~lc[o] ? st[lc[o]] : 0) + (~rc[o] ? st[rc[o]] : 0);
    }
 
    int query(int l, int r, int ql, int qr, int o) {
        if (l >= ql && r <= qr)
            return st[o];
 
        if (l >= qr || ql >= r) return 0;
        int res = 0;
        if (lc[o] != -1) res += query(l, (l + r) >> 1, ql, qr, lc[o]);
        if (rc[o] != -1) res += query((l + r) >> 1, r, ql, qr, rc[o]);
        return res;
    }
}
 
int root[maxn];
 
bool check(const vector<pair<int, int>> &path, int dist, int x) {
    int res = 0;
    for (int i = 0; i < (int)path.size(); ++i)
        res += ~root[x] ? pst::query(0, n, path[i].first, path[i].second, root[x]) : 0;
 
    return res * 2 > dist;
}
 
 
 
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    dfs(0, -1);
    link(0, 0); 
 
    for (int i = 0; i < n; ++i) b[tin[i]] = a[i];
    build(0, n);
 
    memset(root, -1, sizeof(root));
    pst::init();
 
    for (int i = 0; i < n; ++i) {
        if (root[b[i]] == -1)
            root[b[i]] = pst::gnode();
 
        pst::modify(0, n, i, root[b[i]]);
    }
 
    while (q--) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        int lca;
        vector<pair<int, int>> path = qpath(u, v, lca);
        pair<int, int> res = candidate(path);
        int dist = dep[u] + dep[v] - 2 * dep[lca] + 1;
        if (check(path, dist, res.first)) 
            printf("%d\n", res.first);
        else
            puts("-1");
    }
    return 0;
}
