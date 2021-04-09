vector<int> BuildDominatorTree(vector<vector<int>> g, int s) {
    int N = g.size();
    vector<vector<int>> rdom(N), r(N);
    vector<int> dfn(N, -1), rev(N, -1), fa(N, -1), sdom(N, -1), dom(N, -1), val(N, -1), rp(N, -1);
    int stamp = 0;
    auto Dfs = [&](auto dfs, int x) -> void {
        rev[dfn[x] = stamp] = x;
        fa[stamp] = sdom[stamp] = val[stamp] = stamp;
        stamp++;
        for (int u : g[x]) {
            if (dfn[u] == -1) {
                dfs(dfs, u);
                rp[dfn[u]] = dfn[x];
            }
            r[dfn[u]].push_back(dfn[x]);
        }
    };
    function<int(int, int)> Find = [&](int x, int c) {
        if (fa[x] == x) return c ? -1 : x;
        int p = Find(fa[x], 1);
        if (p == -1) return c ? fa[x] : val[x];
        if (sdom[val[x]] > sdom[val[fa[x]]]) val[x] = val[fa[x]];
        fa[x] = p;
        return c ? p : val[x];
    };
    auto Merge = [&](int x, int y) { fa[x] = y; };
    Dfs(Dfs, s);
    for (int i = stamp - 1; i >= 0; --i) {
        for (int u : r[i]) sdom[i] = min(sdom[i], sdom[Find(u, 0)]);
        if (i) rdom[sdom[i]].push_back(i);
        for (int u : rdom[i]) {
            int p = Find(u, 0);
            if (sdom[p] == i) dom[u] = i;
            else dom[u] = p;
        }
        if (i) Merge(i, rp[i]);
    }
    vector<int> res(N, -2);
    res[s] = -1;
    for (int i = 1; i < stamp; ++i) {
        if (sdom[i] != dom[i]) dom[i] = dom[dom[i]];
    }
    for (int i = 1; i < stamp; ++i) res[rev[i]] = rev[dom[i]];
    return res;
}
