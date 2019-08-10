void dfs(int x, int p) {
    dep[x] = ~p ? dep[p] + 1 : dep[x];
    sz[x] = 1;
    to[x] = -1;
    fa[x] = p;
    for (const int &u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
        if (to[x] == -1 || sz[to[x]] < sz[u]) to[x] = u;
    }
}

void hld(int x, int t) {
    static int tk = 0;
    fr[x] = t;
    dfn[x] = tk++;
    if (!~to[x]) return;
    hld(to[x], t);
    for (const int &u : g[x]) {
        if (u == fa[x] || u == to[x]) continue;
        hld(u, u);
    }
}

vector<pair<int, int>> get(int x, int y) {
    int fx = fr[x], fy = fr[y];
    vector<pair<int, int>> res;
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }
        res.emplace_back(dfn[fx], dfn[x] + 1);
        x = fa[fx];
        fx = fr[x];
    }
    res.emplace_back(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]) + 1);
    int lca = (dep[x] < dep[y] ? x : y);
    return res;
}
