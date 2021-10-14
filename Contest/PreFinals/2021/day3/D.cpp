#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 100'000 + 1;
int64_t dist[kN][20];
bool vis[kN][20];
vector<pair<int, int>> g[kN];
vector<tuple<int, int, int, int>> dg[kN];
int dep[kN];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  for (int i = 1; i <= N; ++i) {
    int x = i;
    while (x > 0) {
      dep[i]++;
      x >>= 1;
    }
  }

  for (int i = 1; i <= N; ++i) {
    int f = i;
    for (int j = 0; j <= dep[i]; ++j) {
      for (auto [u, w] : g[i]) {
        if (dep[f] > dep[u])
          dg[f].emplace_back(i, j, u, w);
      }
      f >>= 1;
    }
  }

  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  // vector<vector<bool>> vis(N + 1, vector<bool>(20));
  // vector<vector<int64_t>> dist(N + 1, vector<int64_t>(20, kInf));
  // auto GetDist = [&](auto dfs, int x, int d) -> int64_t {
  //   if (vis[x][d]) return dist[x][d];
  //   if (d == 0) return 0;
  //   int y = x;
  //   for (int i = 0; i < d; ++i) y >>= 1;
  //   for (auto [u, w] : g[x]) {
  //     if (dep[u] > dep[x]) {
  //       dist[x][d] = min(dist[x][d], dfs(dfs, u, d + dep[u] - dep[x]) + w);
  //     } else {
  //       if (dep[u] < dep[y]) {
  //         dist[x][d] = min(dist[x][d], dfs(dfs, y, dep[y] - dep[u]) + w);
  //       } else {
  //         dist[x][d] = min(dist[x][d], dfs(dfs, u, dep[u] - dep[y]) + w);
  //       }
  //     }
  //   }
  //   vis[x][d] = true;
  //   return dist[x][d];
  // };

  priority_queue<tuple<int64_t, int, int>> pq;
  for (int i = 0; i <= N; ++i) pq.emplace(0, i, 0);
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j < 20; ++j) dist[i][j] = kInf;
  }
  for (int i = 0; i <= N; ++i) dist[i][0] = 0;
  while (!pq.empty()) {
    auto [_, x, d] = pq.top();
    pq.pop();
    if (vis[x][d]) continue;
    vis[x][d] = true;
    for (auto [u, w] : g[x]) {
      if (dep[u] < dep[x] && d >= (dep[x] - dep[u])) {
        if (dist[u][d - (dep[x] - dep[u])] > dist[x][d] + w) {
          dist[u][d - (dep[x] - dep[u])] = dist[x][d] + w;
          pq.emplace(-dist[u][d - (dep[x] - dep[u])], u, d - (dep[x] - dep[u]));
        }
      } else if (dep[u] >= dep[x]) {
        if (dist[u][d + (dep[u] - dep[x])] > dist[x][d] + w) {
          dist[u][d + (dep[u] - dep[x])] = dist[x][d] + w;
          pq.emplace(-dist[u][d + (dep[u] - dep[x])], u, d + (dep[u] - dep[x]));
        }
      }
    }
    for (auto [u, e, v, w] : dg[x]) {
      if (dep[v] != dep[x] - d) continue;
      if (dist[u][e] > dist[x][d] + w) {
        dist[u][e] = dist[x][d] + w;
        pq.emplace(-dist[u][e], u, e);
      }
    }
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int s, t;
    cin >> s >> t;
    int64_t ans = kInf;
    int x = s, y = t, a = 0, b = 0;
    while (x != y) {
      if (dep[x] > dep[y]) a++, x >>= 1;
      else b++, y >>= 1;
    }
    while (x > 0) {
      ans = min(ans, dist[s][a] + dist[t][b]);
      x >>= 1;
      a++;
      b++;
    }
    // while (x > 0) {
    //   ans = min(ans, GetDist(GetDist, s, a) + GetDist(GetDist, t, b));
    //   x >>= 1;
    //   a++;
    //   b++;
    // }
    if (ans == kInf) ans = -1;
    cout << ans << "\n";
  }
  return 0;
}

