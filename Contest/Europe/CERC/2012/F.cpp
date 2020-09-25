#include <bits/stdc++.h>
using namespace std;

double Solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> g(N);
    for (int i = 0; i < M; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        g[x].emplace_back(y, w);
        g[y].emplace_back(x, w);
    }

    auto Dijkstra = [&](int s) {
        vector<int64_t> dist(N, 1'000'000'000'000'000'000);
        dist[s] = 0;
        priority_queue<pair<int64_t, int>> pq;
        pq.emplace(0, s);
        vector<bool> vis(N);
        while (!pq.empty()) {
            int x = pq.top().second;
            pq.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (auto &e : g[x]) {
                if (dist[e.first] > dist[x] + e.second) {
                    dist[e.first] = dist[x] + e.second;
                    pq.emplace(-dist[e.first], e.first);
                }
            }
        }
        return dist;
    };

    vector<int64_t> X = Dijkstra(0);
    vector<int64_t> Y = Dijkstra(1);
    for (int i = 0; i < N; ++i) {
        int64_t Z = X[i] + Y[i];
        X[i] -= Y[i];
        Y[i] = Z;
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    int64_t P = X[N / 2];
    int64_t Q = Y[N / 2];
    int64_t S = 0;
    for (int i = 0; i < N; ++i) {
        S += abs(X[i] - P);
        S += abs(Y[i] - Q);
    }
    return static_cast<double>(S) / N / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cout << fixed << setprecision(20) << Solve() << "\n";
    }
}

