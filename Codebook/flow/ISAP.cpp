struct isap {
    static const int inf = 1e9;
    struct edge {
        int dest, cap, rev;
        edge(int a, int b, int c): dest(a), cap(b), rev(c) {}
    };
    vector<edge> g[maxn];
    int it[maxn], gap[maxn], d[maxn];
    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size() - 0);
        g[b].emplace_back(a, 0, g[a].size() - 1);
    }
    int dfs(int x, int t, int tot, int flow) {
        if (x == t) return flow;
        for (int &i = it[x]; i < g[x].size(); ++i) {
            edge &e = g[x][i];
            if (e.cap > 0 && d[e.dest] == d[x] - 1) {
                int f = dfs(e.dest, t, tot, min(flow, e.cap));
                if (f) {
                    e.cap -= f;
                    g[e.dest][e.rev].cap += f;
                    return f;
                }
            }
        }
        if ((--gap[d[x]]) == 0) d[x] = tot;
        else d[x]++, it[x] = 0, ++gap[d[x]];
        return 0;
    }
    int operator()(int s, int t, int tot) {
        memset(it, 0, sizeof(it));
        memset(gap, 0, sizeof(gap));
        memset(d, 0, sizeof(d));
        int r = 0;
        gap[0] = tot;
        for (; d[s] < tot; r += dfs(s, t, tot, inf));
        return r;
    }
};
