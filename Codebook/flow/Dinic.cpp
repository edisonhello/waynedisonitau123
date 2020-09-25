struct Edge {
    int to, cap, rev;
    Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};
int Flow(vector<vector<Edge>> g, int s, int t) {
    int n = g.size(), res = 0;
    vector<int> lev(n, -1), iter(n);
    while (true) {
        vector<int> que(1, s);
        fill(lev.begin(), lev.end(), -1);
        fill(iter.begin(), iter.end(), 0);
        lev[s] = 0;
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            for (Edge &e : g[x]) {
                if (e.cap > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    que.push_back(e.to);
                }
            }
        }
        if (lev[t] == -1) break;
        auto Dfs = [&](auto dfs, int x, int f = 1000000000) {
            if (x == t) return f;
            int res = 0;
            for (int &it = iter[x]; it < g[x].size(); ++it) {
                Edge &e = g[x][it];
                if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                    int p = dfs(dfs, e.to, min(f - res, e.cap));
                    res += p;
                    e.cap -= p;
                    g[e.to][e.rev].cap += p;
                }
            }
            if (res == 0) lev[x] = -1;
            return res;
        };
        res += Dfs(Dfs, s);
    }
    return res;
}
