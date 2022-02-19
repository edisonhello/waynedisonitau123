#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> w(M);
  for (int i = 0; i < M; ++i) {
    cin >> w[i];
  }
  vector<vector<int>> g(N);
  vector<int> u(M), v(M), c(M);
  for (int i = 0; i < M; ++i) {
    cin >> u[i] >> v[i] >> c[i];
    u[i]--;
    v[i]--;
    c[i]--;
    g[u[i]].push_back(i);
    g[v[i]].push_back(i);
  }
  vector<int> que = {0};
  vector<int> dist(N, -1);
  dist[0] = 0;
  for (int it = 0; it < que.size(); ++it) {
    int x = que[it];
    for (int e : g[x]) {
      int y = u[e] ^ v[e] ^ x;
      if (dist[y] == -1) {
        dist[y] = dist[x] + 1;
        que.push_back(y);
      }
    }
  }
  vector<vector<int>> dg(N);
  for (int x = 0; x < N; ++x) {
    for (int e : g[x]) {
      int y = u[e] ^ v[e] ^ x;
      if (dist[y] == dist[x] + 1) {
        dg[x].push_back(e);
      }
    }
  }

  vector<int> cnt(M);
  vector<int> ans(N, 1'000'000'000);

  auto BruteForce = [&](auto self, int x, int s) -> void {
    ans[x] = min(ans[x], s);
    for (int e : dg[x]) {
      int y = u[e] ^ v[e] ^ x;
      ++cnt[c[e]];
      self(self, y, s + cnt[c[e]] * w[c[e]]);
      --cnt[c[e]];
    }
  };

  BruteForce(BruteForce, 0, 0);
  for (int i = 1; i < N; ++i) {
    cout << ans[i] << "\n";
  }
}

