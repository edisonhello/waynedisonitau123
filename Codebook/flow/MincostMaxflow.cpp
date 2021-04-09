struct Edge {
    int to, cap, rev, w;
    Edge(int t, int c, int r, int w) : to(t), cap(c), rev(r), w(w) {}
};
pair<int, int> Flow(vector<vector<Edge>> g, int s, int t) {
    int N = g.size();
    vector<int> dist(N), ed(N), pv(N);
    vector<bool> inque(N);
    int flow = 0, cost = 0;
    while (true) {
        dist.assign(N, kInf);
        inque.assign(N, false);
        pv.assign(N, -1);
        dist[s] = 0;
        queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int x = que.front(); que.pop();
            inque[x] = false;
            for (int i = 0; i < g[x].size(); ++i) {
                Edge &e = g[x][i];
                if (e.cap > 0 && dist[e.to] > dist[x] + e.w) {
                    dist[e.to] = dist[x] + e.w;
                    pv[e.to] = x;
                    ed[e.to] = i;
                    if (!inque[e.to]) {
                        inque[e.to] = true;
                        que.push(e.to);
                    }
                }
            }
        }
        if (dist[t] == kInf) break;
        int f = kInf;
        for (int x = t; x != s; x = pv[x]) f = min(f, g[pv[x]][ed[x]].cap);
        for (int x = t; x != s; x = pv[x]) {
            Edge &e = g[pv[x]][ed[x]];
            e.cap -= f;
            g[e.to][e.rev].cap += f;
        }
        flow += f;
        cost += f * dist[t];
    }
    return make_pair(flow, cost);
}
