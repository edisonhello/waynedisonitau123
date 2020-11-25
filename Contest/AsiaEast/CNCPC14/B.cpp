#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev, w;

    Edge(int t, int c, int r, int w) : to(t), cap(c), rev(r), w(w) {}
};

int Flow(vector<vector<Edge>> g, int S, int T) {
    int N = g.size();
    vector<int> dist(N, -1'000'000'000);
    vector<bool> inque(N);
    vector<int> pv(N, -1), ed(N);
    int Cost = 0, Flow = 0;
    while (true) {
        fill(dist.begin(), dist.end(), -1'000'000'000);
        fill(inque.begin(), inque.end(), false);
        fill(pv.begin(), pv.end(), -1);
        dist[S] = 0;
        queue<int> Que;
        Que.push(S);
        while (!Que.empty()) {
            int x = Que.front();
            Que.pop();
            inque[x] = false;
            for (int i = 0; i < g[x].size(); ++i) {
                const auto &E = g[x][i];
                if (E.cap == 0) continue;
                if (dist[E.to] < dist[x] + E.w) {
                    dist[E.to] = dist[x] + E.w;
                    pv[E.to] = x;
                    ed[E.to] = i;
                    if (!inque[E.to]) {
                        inque[E.to] = true;
                        Que.push(E.to);
                    }
                }
            }
        }
        if (dist[T] == -1'000'000'000) break;
        int F = 1'000'000'000;
        for (int x = T; x != S; x = pv[x]) F = min(F, g[pv[x]][ed[x]].cap);
        Cost += F * dist[T];
        for (int x = T; x != S; x = pv[x]) {
            Edge &E = g[pv[x]][ed[x]];
            E.cap -= F;
            g[E.to][E.rev].cap += F;
        }
        Flow += F;
    }
    return Cost;
}

int Solve() {
    int N, M, P;
    cin >> N >> M >> P;
    vector<vector<int>> V(3, vector<int>(N));

    vector<vector<Edge>> g(6 * N + 3);

    auto AddEdge = [&](int a, int b, int c, int d) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0, +d);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1, -d);
    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) cin >> V[i][j];
    }
    for (int i = 0; i < 3 * N; ++i) AddEdge(i, i + N * 3, 1, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            AddEdge(j + N + N * 3, i, 1, (V[0][i] + V[1][j]) * (V[0][i] ^ V[1][j]) % P);
            AddEdge(i + N * 3, j + N + N, 1, (V[0][i] + V[2][j]) * (V[0][i] ^ V[2][j]) % P);
        }
    }
    for (int i = 0; i < N; ++i) AddEdge(6 * N, i + N, 2, 0);
    for (int i = 0; i < N; ++i) AddEdge(i + N + N + N * 3, 6 * N + 1, 1, 0);
    AddEdge(6 * N + 2, 6 * N, M, 0);
    return Flow(g, 6 * N + 2, 6 * N + 1);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cout << Solve() << "\n";
    }
}

