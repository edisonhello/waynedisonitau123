#include <bits/stdc++.h>
using namespace std;

int main() {
  int t, r;
  cin >> t >> r;

  int N, M;
  cin >> N >> M;
  vector<vector<pair<int, int>>> g(N);
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  int K;
  cin >> K;
  vector<int> a(K), p(K);
  for (int i = 0; i < K; ++i) {
    cin >> a[i] >> p[i];
    a[i]--;
    p[i] = 100 - p[i];
  }

  constexpr int64_t kInf = 1'000'000'000'000'000;

  auto Dijk = [&](int s) {
    vector<int64_t> dist(N, kInf);
    vector<bool> vis(N);
    dist[s] = 0;
    priority_queue<pair<int64_t, int>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
      int x = pq.top().second;
      pq.pop();
      if (vis[x]) {
        continue;
      }
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

  auto d0 = Dijk(0);
  if (d0[N - 1] == kInf) {
    cout << "-1\n";
    return 0;
  }

  auto dn = Dijk(N - 1);

  vector<vector<int64_t>> dist(K + 1, vector<int64_t>(K + 1));
  for (int i = 0; i < K; ++i) {
    dist[0][i + 1] = dist[i + 1][0] = d0[a[i]];
    auto d = Dijk(a[i]);
    for (int j = 0; j < K; ++j) {
      dist[i + 1][j + 1] = d[a[j]];
    }
  }

  constexpr double kDInf = 1E20;
  vector<vector<double>> dp(1 << (K + 1), vector<double>(K + 1, kDInf));
  vector<vector<bool>> vis(1 << (K + 1), vector<bool>(K + 1));

  auto Dfs = [&](auto self, int mask, int x) -> double {
    if (vis[mask][x]) {
      return dp[mask][x];
    }
    vis[mask][x] = true;
    if (x == 0) {
      assert(mask == 1);
      for (int y = 1; y <= K; ++y) {
        dp[mask][x] = min(dp[mask][x], self(self, mask ^ (1 << y), y) + static_cast<double>(dist[x][y]) / t);
      }
      dp[mask][x] = min(dp[mask][x], static_cast<double>(d0[N - 1]) / t);
    } else {
      for (int y = 1; y <= K; ++y) {
        if (mask >> y & 1) {
          continue;
        }
        dp[mask][x] = min(dp[mask][x], self(self, mask ^ (1 << y), y) +
                                           static_cast<double>(dist[x][y]) / t);
      }
      dp[mask][x] = min(dp[mask][x], static_cast<double>(dn[a[x - 1]]) / t);
      double pr = static_cast<double>(p[x - 1]) / 100;
      dp[mask][x] = (1 - pr) * dp[mask][x] + pr * static_cast<double>(dn[a[x - 1]]) / r;
    }
    return dp[mask][x];
  };

  cout << fixed << setprecision(20) << Dfs(Dfs, 1, 0) << "\n";
}

