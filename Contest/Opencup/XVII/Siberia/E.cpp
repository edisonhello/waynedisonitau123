#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev, w;
    Edge(int a, int b, int c, int d) : to(a), cap(b), rev(c), w(d) {}
};

constexpr int64_t kInf = 1'000'000'000'000'000;

int64_t Flow(vector<vector<Edge>> &g, int s, int t) {
    int n = g.size();
    vector<int64_t> dist(n, kInf);
    vector<bool> inque(n);
    vector<int> pv(n), ed(n);
    int64_t res = 0;
    while (true) {
        fill(dist.begin(), dist.end(), kInf);
        fill(inque.begin(), inque.end(), false);
        fill(pv.begin(), pv.end(), -1);
        fill(ed.begin(), ed.end(), -1);
        dist[s] = 0;
        vector<int> que(1, s);
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            inque[x] = false;
            for (int i = 0; i < g[x].size(); ++i) {
                const Edge &e = g[x][i];
                if (e.cap == 0) continue;
                if (dist[x] + e.w < dist[e.to]) {
                    dist[e.to] = dist[x] + e.w;
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
        int dlt = 1'000'000'000;
        for (int x = t; x != s; x = pv[x]) {
            dlt = min(dlt, g[pv[x]][ed[x]].cap);
        }
        for (int x = t; x != s; x = pv[x]) {
            Edge &e = g[pv[x]][ed[x]];
            e.cap -= dlt;
            g[e.to][e.rev].cap += dlt;
        }
        res += dist[t] * dlt;
    }
    return res;
}

int main() {
    int n, k, t;
    cin >> n >> k >> t;
    t--;
    vector<vector<int>> c(n, vector<int>(k + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            cin >> c[i][j];
        }
    }
    int64_t res = kInf;

    auto Solve = [&](int x) {
        vector<vector<Edge>> g(2 + n + k + 1 + 1);

        auto AddEdge = [&](int a, int b, int c, int d) {
            g[a].emplace_back(b, c, (int)g[b].size() - 0, +d);
            g[b].emplace_back(a, 0, (int)g[a].size() - 1, -d);
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                AddEdge(i, j + n, 1, c[i][j]);
            }
            AddEdge(n + k + 1, i, 1, 0);
        }
        for (int i = 0; i < k; ++i) {
            if (i == t) AddEdge(i + n, n + k + 1 + 1, x, 0);
            else AddEdge(i + n, n + k + 1 + 2, x - 1, 0);
        }
        AddEdge(k + n, n + k + 1 + 2, 200, 0);
        AddEdge(n + k + 1 + 2, n + k + 1 + 1, n - x, 0);
        int64_t res = Flow(g, n + k + 1, n + k + 1 + 1);
        vector<int> vote(n, -1);
        for (int i = 0; i < n; ++i) {
            for (Edge &e : g[i]) {
                if (e.cap == 0) {
                    vote[i] = e.to - n;
                }
            }
        }
        return make_pair(res, vote);
    };

    vector<int> vote(n, -1);

    for (int x = 1; x <= n; ++x) {
        auto p = Solve(x);
        if (p.first < res) {
            res = p.first;
            vote = p.second;
        }
    }
    cout << res << "\n";
    for (int i = 0; i < n; ++i) cout << vote[i] + 1 << " ";
    cout << "\n";
}

