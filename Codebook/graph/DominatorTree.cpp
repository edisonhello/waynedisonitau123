namespace dominator {
    vector<int> g[maxn], r[maxn], rdom[maxn];
    int dfn[maxn], rev[maxn], fa[maxn], sdom[maxn], dom[maxn], val[maxn], rp[maxn], tk;
    void add_edge(int x, int y) {
        g[x].push_back(y);
    }
    void dfs(int x) {
        rev[dfn[x] = tk] = x;
        fa[tk] = sdom[tk] = val[tk] = tk;
        tk++;
        for (const int &u : g[x]) {
            if (dfn[u] == -1) dfs(u), rp[dfn[u]] = dfn[x];
            r[dfn[u]].push_back(dfn[x]);
        } 
    }
    void merge(int x, int y) {
        fa[x] = y;
    }
    int find(int x, int c = 0) {
        if (fa[x] == x) return x;
        int p = find(fa[x], 1);
        if (p == -1) return c ? fa[x] : val[x];
        if (sdom[val[x]] > sdom[val[fa[x]]]) val[x] = val[fa[x]];
        fa[x] = p;
        return c ? p : val[x];
    }
    vector<int> build(int s) {
        memset(dfn, -1, sizeof(dfn));
        memset(rev, -1, sizeof(rev));
        memset(fa, -1, sizeof(fa));
        memset(val, -1, sizeof(val));
        memset(sdom, -1, sizeof(sdom));
        memset(rp, -1, sizeof(rp));
        memset(dom, -1, sizeof(dom));
        tk = 0, dfs(s);
        for (int i = tk - 1; i >= 0; --i) {
            for (const int &u : r[i]) sdom[i] = min(sdom[i], sdom[find(u)]);
            if (i) rdom[sdom[i]].push_back(i);
            for (const int &u : rdom[i]) {
                int p = find(u);
                if (sdom[p] == i) dom[u] = i;
                else dom[u] = p;
            }
            if (i) merge(i, rp[i]);
        }
        vector<int> p(maxn, -1);
        for (int i = 1; i < tk; ++i) if (sdom[i] != dom[i]) dom[i] = dom[dom[i]];
        for (int i = 1; i < tk; ++i) p[rev[i]] = rev[dom[i]];
        return p;
    }
}
