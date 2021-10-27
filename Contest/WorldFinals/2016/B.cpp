#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, B, S, R;
    cin >> N >> B >> S >> R;
    vector<vector<pair<int, int>>> g(N), rg(N);
    for (int i = 0; i < R; ++i) {
        int u, v, l;
        cin >> u >> v >> l;
        u--;
        v--;
        g[u].emplace_back(v, l);
        rg[v].emplace_back(u, l);
    }

    auto Dijkstra = [&](const auto& g, int s) {
        constexpr int kInf = 1'000'000'000;
        vector<int> dist(N, kInf);
        dist[s] = 0;
        priority_queue<pair<int, int>> pq;
        pq.emplace(0, s);
        vector<bool> vis(N);
        while (!pq.empty()) {
            int x = pq.top().second;
            pq.pop();
            if (vis[x]) continue;
            vis[x] = true;
            for (auto [u, w] : g[x]) {
                if (dist[u] > dist[x] + w) {
                    dist[u] = dist[x] + w;
                    pq.emplace(-dist[u], u);
                }
            }
        }
        return dist;
    };

    auto dist1 = Dijkstra(g, B);
    auto dist2 = Dijkstra(rg, B);
    vector<int> d(B);
    for (int i = 0; i < B; ++i) d[i] = dist1[i] + dist2[i];
    sort(d.begin(), d.end());

    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    vector<vector<int64_t>> dp(B + 1, vector<int64_t>(S + 1, kInf));
    vector<int64_t> sum(B + 1);
    for (int i = 0; i < B; ++i) {
        sum[i + 1] = sum[i] + d[i];
    }

    auto Solve = [&](auto dfs, int l, int r, int tl, int tr, int p) -> void {
        if (l > r) return;
        int m = (l + r) >> 1;
        int best = -1;
        for (int i = tl; i <= min(tr, m - 1); ++i) {
            int64_t v = dp[i][p - 1] + (sum[m] - sum[i]) * (m - i - 1);
            if (v < dp[m][p]) {
                dp[m][p] = v;
                best = i;
            }
        }
        dfs(dfs, l, m - 1, tl, best, p);
        dfs(dfs, m + 1, r, best, tr, p);
    };

    dp[0][0] = 0;

    for (int j = 1; j <= S; ++j) {
        Solve(Solve, j, B, 0, B - 1, j);
    }
    cout << dp[B][S] << "\n";
}

