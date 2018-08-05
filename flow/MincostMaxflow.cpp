struct mincost {
    struct edge {
        int dest, cap, w, rev;
        edge(int a, int b, int c, int d): dest(a), cap(b), w(c), rev(d) {}
    };
    vector<edge> g[maxn];
    int d[maxn], p[maxn], ed[maxn];
    bool inq[maxn];
    void init() {
        for (int i = 0; i < maxn; ++i) g[i].clear();
    }
    void add_edge(int a, int b, int c, int d) {
        g[a].emplace_back(b, c, +d, g[b].size() - 0);
        g[b].emplace_back(a, 0, -d, g[a].size() - 1);
    }
    bool spfa(int s, int t, int &f, int &c) {
        for (int i = 0; i < maxn; ++i) {
            d[i] = inf;
            p[i] = ed[i] = -1;
            inq[i] = false;
        }
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int x = q.front(); q.pop();
            inq[x] = false;
            for (int i = 0; i < g[x].size(); ++i) {
                edge &e = g[x][i];
                if (e.cap > 0 && d[e.dest] > d[x] + e.w) {
                    d[e.dest] = d[x] + e.w;
                    p[e.dest] = x;
                    ed[e.dest] = i;
                    if (!inq[e.dest]) q.push(e.dest), inq[e.dest] = true;
                }
            }
        }
        if (d[t] == inf) return false;
        int dlt = inf;
        for (int x = t; x != s; x = p[x]) dlt = min(dlt, g[p[x]][ed[x]].cap);
        for (int x = t; x != s; x = p[x]) {
            edge &e = g[p[x]][ed[x]];
            e.cap -= dlt;
            g[e.dest][e.rev].cap += dlt;
        }
        f += dlt; c += d[t] * dlt;
        return true;
    }
    pair<int, int> operator()(int s, int t) {
        int f = 0, c = 0;
        while (spfa(s, t, f, c));
        return make_pair(f, c);
    }
};

