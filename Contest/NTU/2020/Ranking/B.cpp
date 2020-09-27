#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M, S, W;
    cin >> N >> M >> S >> W;

    vector<bool> red(N), blue(N);
    for (int i = 0; i < S; ++i) {
        int x;
        cin >> x;
        red[x - 1] = true;
    }
    for (int i = 0; i < W; ++i) {
        int x;
        cin >> x;
        blue[x - 1] = true;
    }

    vector<vector<pair<int, int>>> g(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    priority_queue<tuple<int64_t, int, int>> pq;
    pq.emplace(0, 0, red[0]);

    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    vector<vector<int64_t>> dist(N, vector<int64_t>(2, kInf));
    vector<vector<bool>> used(N, vector<bool>(2));
    dist[0][red[0]] = 0;

    while (!pq.empty()) {
        int x = get<1>(pq.top());
        int y = get<2>(pq.top());
        pq.pop();
        if (used[x][y]) continue;
        used[x][y] = true;
        for (auto &e : g[x]) {
            if (dist[e.first][y || red[e.first]] > dist[x][y] + e.second) {
                dist[e.first][y || red[e.first]] = dist[x][y] + e.second;
                pq.emplace(-dist[e.first][y || red[e.first]], e.first, y || red[e.first]);
            }
        }
    }
    int64_t res = kInf;
    for (int i = 0; i < N; ++i) {
        if (blue[i]) {
            res = min(res, dist[i][1]);
        }
    }
    cout << res << "\n";
}
