#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> g(N);
  vector<int> deg(N);
  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    uf[x] = y;
  };

  vector<bool> leaf(N);

  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
    deg[u]++;
    deg[v]++;
    Merge(u, v);
  }

  for (int i = 0; i < N; ++i) {
    if (deg[i] == 1) {
      leaf[i] = true;
    }
  }

  vector<vector<int>> nd(N);
  for (int i = 0; i < N; ++i) {
    nd[Find(i)].push_back(i);
  }

  vector<int> to(N, -1);
  vector<bool> mark(N);
  vector<pair<int, int>> ans;
  for (int i = 0; i < N; ++i) {
    if (nd[i].empty()) continue;
    queue<int> que;
    int cnt = 0;
    for (int u : nd[i]) {
      if (deg[u] == 1) {
        que.push(u);
        mark[u] = true;
        cnt++;
      }
    }
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      for (int u : g[x]) {
        if (mark[u]) continue;
        assert(to[x] == -1);
        to[x] = u;
        if (--deg[u] == 1) {
          mark[u] = true;
          cnt++;
          que.push(u);
        }
      }
    }
    if (cnt < nd[i].size()) {
      for (int u : nd[i]) {
        if (mark[u]) continue;
        for (int x : g[u]) {
          if (mark[x] && to[x] == u) {
            ans.emplace_back(u, x);
          }
        }
      }
    } else {
      if (nd[i].size() > 1) {
        for (int u : nd[i]) {
          if (leaf[u]) {
            ans.emplace_back(u, g[u][0]);
          }
        }
      }
    }
  }
  sort(ans.begin(), ans.end());
  cout << ans.size() << "\n";
  for (auto [x, y] : ans) cout << x + 1 << " " << y + 1 << "\n";
  return 0;
}

