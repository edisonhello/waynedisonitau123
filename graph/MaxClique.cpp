struct MaxClique {
    int n, deg[maxn], ans;
    bitset<maxn> adj[maxn];
    vector<pair<int, int>> edge;
    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; ++i) adj[i].reset();
        for (int i = 0; i < n; ++i) deg[i] = 0;
        edge.clear();
    }
    void add_edge(int a, int b) {
        edge.emplace_back(a, b);
        ++deg[a]; ++deg[b];
    }
    int solve() {
        vector<int> ord;
        for (int i = 0; i < n; ++i) ord.push_back(i);
        sort(ord.begin(), ord.end(), [&](const int &a, const int &b) { return deg[a] < deg[b]; });
        vector<int> id(n);
        for (int i = 0; i < n; ++i) id[ord[i]] = i;
        for (auto e : edge) {
            int u = id[e.first], v = id[e.second];
            adj[u][v] = adj[v][u] = true;
        }
        bitset<maxn> r, p;
        for (int i = 0; i < n; ++i) p[i] = true;
        ans = 0;
        dfs(r, p);
        return ans;
    }
    void dfs(bitset<maxn> r, bitset<maxn> p) {
        if (p.count() == 0) return ans = max(ans, (int)r.count()), void();
        if ((r | p).count() <= ans) return;
        int now = p._Find_first();
        bitset<maxn> cur = p & ~adj[now];
        for (now = cur._Find_first(); now < n; now = cur._Find_next(now)) {
            r[now] = true;
            dfs(r, p & adj[now]);
            r[now] = false;
            p[now] = false;
        }
    }
};
