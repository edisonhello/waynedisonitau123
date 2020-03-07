#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge {
        int to, cap, rev, flow;
        bool real;
        Edge(int a, int b, int c, bool d) : to(a), cap(b), rev(c), real(d), flow(0) {}
    };

    vector<vector<Edge>> g;
    vector<int> lev;
    vector<int> iter;

    Dinic(int n) {
        g.resize(n);
        lev.resize(n);
        iter.resize(n);
    }

    void AddEdge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0, true);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1, false);
    }

    bool Bfs(int s, int t) {
        fill(lev.begin(), lev.end(), -1);
        lev[s] = 0;
        vector<int> que(1, s);
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            for (Edge &e : g[x]) {
                if (e.cap == 0) continue;
                if (lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    que.push_back(e.to);
                }
            }
        }
        return lev[t] != -1;
    }

    int Flow(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (int &it = iter[x]; it < g[x].size(); ++it) {
            Edge &e = g[x][it];
            if (e.cap == 0) continue;
            if (lev[e.to] != lev[x] + 1) continue;
            int f = Flow(e.to, t, min(flow - res, e.cap));
            e.cap -= f;
            e.flow += f;
            g[e.to][e.rev].cap += f;
            g[e.to][e.rev].flow -= f;
            res += f;
        }
        if (!res) lev[x] = -1;
        return res;
    }

    int operator()(int s, int t) {
        int res = 0;
        while (Bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            res += Flow(s, t, 1'000'000'000);
        }
        return res;
    }
};

int main() {
    int n, m, c;
    scanf("%d%d%d", &n, &m, &c);
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int x, y, t;
        scanf("%d%d%d", &x, &y, &t);
        x--, y--;
        g[x].emplace_back(y, t);
        g[y].emplace_back(x, t);
    }
    priority_queue<pair<int, int>> pq;
    vector<int> dist(n, 1'000'000'000);
    dist[0] = 0;
    pq.emplace(0, 0);
    vector<int> used(n);
    while (!pq.empty()) {
        int x = pq.top().second;
        pq.pop();
        if (used[x]++) continue;
        for (auto &e : g[x]) {
            int u = e.first, w = e.second;
            if (dist[u] > dist[x] + w) {
                dist[u] = dist[x] + w;
                pq.emplace(-dist[u], u);
            }
        }
    }
    vector<pair<int, int>> ed;
    for (int i = 0; i < n; ++i) {
        for (auto &e : g[i]) {
            if (dist[i] == dist[e.first] + e.second) {
                // flow.AddEdge(i, e.first, 1);
                ed.emplace_back(i, e.first);
            }
        }
    }
    vector<int> bus(c);
    vector<int> cnt(n);
    for (int i = 0; i < c; ++i) {
        scanf("%d", &bus[i]);
        bus[i]--;
        cnt[bus[i]]++;
    }
    sort(bus.begin(), bus.end(), [&](int i, int j) { return dist[i] < dist[j]; });
    int ans = 0;
    for (int i = 0, j = 0; i < bus.size(); i = j) {
        Dinic flow(n + 1);
        for (auto &e : ed) flow.AddEdge(e.first, e.second, 1);
        vector<int> bs;
        for (j = i; j < bus.size() && dist[bus[i]] == dist[bus[j]]; ++j) bs.push_back(bus[j]);
        sort(bs.begin(), bs.end());
        bs.resize(unique(bs.begin(), bs.end()) - bs.begin());
        for (int u : bs) flow.AddEdge(n, u, cnt[u]);
        ans += flow(n, 0);
        // for (int u : bs) flow.AddEdge(u, 0, cnt[u]);
    }
    printf("%d\n", ans);
}
