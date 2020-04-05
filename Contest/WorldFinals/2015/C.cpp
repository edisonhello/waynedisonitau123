#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev, cost;
    Edge(int a, int b, int c, int d) : to(a), cap(b), rev(c), cost(d) {}
};

constexpr int kInf = 1'000'000'000;

int64_t Flow(vector<vector<Edge>> &g, int s, int t) {
    int n = g.size();
    vector<int> dist(n, kInf), pv(n, -1), ed(n, -1);
    vector<bool> inque(n, false);
    int64_t scost = 0;
    int sflow = 0;
    while (true) {
        fill(dist.begin(), dist.end(), kInf);
        fill(inque.begin(), inque.end(), false);
        dist[s] = 0;
        vector<int> que(1, s);
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            inque[x] = false;
            for (int i = 0; i < g[x].size(); ++i) {
                Edge &e = g[x][i];
                if (e.cap == 0) continue;
                if (dist[e.to] > dist[x] + e.cost) {
                    dist[e.to] = dist[x] + e.cost;
                    pv[e.to] = x;
                    ed[e.to] = i;
                    if (!inque[e.to]) {
                        inque[e.to] = true;
                        que.push_back(e.to);
                    }
                }
            }
        }
        if (dist[t] == kInf) break;
        int flow = kInf;
        for (int x = t; x != s; x = pv[x]) flow = min(flow, g[pv[x]][ed[x]].cap);
        for (int x = t; x != s; x = pv[x]) {
            Edge &e = g[pv[x]][ed[x]];
            e.cap -= flow;
            g[x][e.rev].cap += flow;
        }
        sflow += flow;
        scost += 1LL * flow * dist[t];
    }
    return scost;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cin >> dist[i][j];
        }
    }
    vector<vector<Edge>> g(n + n + 4);

    auto AddEdge = [&](int a, int b, int c, int d) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0, d);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1, -d);
    };

    int s = n + n + 2, t = n + n + 3;

    for (int i = 0; i <= n; ++i) {
        if (i == 0) AddEdge(s, i, k, 0);
        else AddEdge(s, i, 1, 0);
        for (int j = i + 1; j <= n; ++j) {
            AddEdge(i, j + n + 1, 1, dist[i][j]);
        }
        AddEdge(i + n + 1, t, 1, 0);
    }
    cout << Flow(g, s, t) << "\n";
}

