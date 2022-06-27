#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, K;
  cin >> N >> M >> K;
  int t;
  cin >> t;
  constexpr int64_t kInf = 1'000'000'000'000'000;
  vector<vector<int64_t>> g(N, vector<int64_t>(N, kInf));
  for (int i = 0; i < N; ++i) {
    g[i][i] = 0;
  }
  for (int i = 0; i < M; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    g[a][b] = min<int64_t>(g[a][b], c);
    g[b][a] = min<int64_t>(g[b][a], c);
  }
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
  vector<int> s(K);
  vector<bool> vis(N);
  for (int i = 0; i < K; ++i) {
    cin >> s[i];
    s[i]--;
    vis[s[i]] = true;
  }
  int64_t ans = 0;
  for (int i = 0; i < N; ++i) {
    if (!vis[i]) {
      int64_t dist = kInf;
      for (int j = 0; j < K; ++j) {
        dist = min(dist, g[i][s[j]]);
      }
      ans = max(ans, 2 * dist);
    }
  }
  vector<tuple<int64_t, int, int>> edges;
  for (int i = 0; i < K; ++i) {
    for (int j = i + 1; j < K; ++j) {
      edges.emplace_back(g[s[i]][s[j]], s[i], s[j]);
    }
  }
  sort(edges.begin(), edges.end());
  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  for (auto [w, u, v] : edges) {
    if (Find(u) != Find(v)) {
      ans = max(ans, w);
      uf[Find(u)] = Find(v);
    }
  }
  if (ans >= kInf || t == 0 && ans != 0) {
    cout << -1 << "\n";
  } else {
    if (t == 0) {
      cout << 0 << "\n";
    } else {
      cout << (ans + t - 1) / t << "\n";
    }
  }
}
