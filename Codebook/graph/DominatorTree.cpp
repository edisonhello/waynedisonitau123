namespace dominator {
vector<int> g[maxn], r[maxn], rdom[maxn];
int dfn[maxn], rev[maxn], fa[maxn], sdom[maxn], dom[maxn], val[maxn], rp[maxn], tk;
void init(int n) {
    // vertices are numbered from 0 to n - 1
    fill(dfn, dfn + n, -1);
    fill(rev, rev + n, -1);
    fill(fa, fa + n, -1);
    fill(val, val + n, -1);
    fill(sdom, sdom + n, -1);
    fill(rp, rp + n, -1);
    fill(dom, dom + n, -1);
    tk = 0;
    for (int i = 0; i < n; ++i)
        g[i].clear();
}
void add_edge(int x, int y) {
    g[x].push_back(y);
}
void dfs(int x) {
    rev[dfn[x] = tk] = x;
    fa[tk] = sdom[tk] = val[tk] = tk;
    tk++;
    for (int u : g[x]) {
        if (dfn[u] == -1) dfs(u), rp[dfn[u]] = dfn[x];
        r[dfn[u]].push_back(dfn[x]);
    } 
}
void merge(int x, int y) {
    fa[x] = y;
}
int find(int x, int c = 0) {
    if (fa[x] == x) return c ? -1 : x;
    int p = find(fa[x], 1);
    if (p == -1) return c ? fa[x] : val[x];
    if (sdom[val[x]] > sdom[val[fa[x]]]) val[x] = val[fa[x]];
    fa[x] = p;
    return c ? p : val[x];
}
vector<int> build(int s, int n) {
    // return the father of each node in the dominator tree
    // p[i] = -2 if i is unreachable from s
    dfs(s);
    for (int i = tk - 1; i >= 0; --i) {
        for (int u : r[i]) sdom[i] = min(sdom[i], sdom[find(u)]);
        if (i) rdom[sdom[i]].push_back(i);
        for (int &u : rdom[i]) {
            int p = find(u);
            if (sdom[p] == i) dom[u] = i;
            else dom[u] = p;
        }
        if (i) merge(i, rp[i]);
    }
    vector<int> p(n, -2);
    p[s] = -1;
    for (int i = 1; i < tk; ++i) if (sdom[i] != dom[i]) dom[i] = dom[dom[i]];
    for (int i = 1; i < tk; ++i) p[rev[i]] = rev[dom[i]];
    return p;
}}
