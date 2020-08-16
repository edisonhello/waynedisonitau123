#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  vector<bool> marked(n);

  vector<int> buf;
  auto Dfs = [&](auto dfs, int x, int s = 0, int p = -1) -> void {
    if (marked[x]) buf.push_back(s);
    for (auto [u, w] : g[x]) {
      if (u == p) continue;
      dfs(dfs, u, s + w, x);
    }
  };

  for (int i = 0; i < m; ++i) {
    int t, x;
    cin >> t >> x;
    x--;
    if (t == 1) {
      marked[x] = true;
    }
    if (t == 2) {
      marked[x] = false;
    }
    if (t == 3) {
      int k;
      cin >> k;
      buf.clear();
      Dfs(Dfs, x);
      sort(buf.begin(), buf.end());
      cout << buf[k - 1] << "\n";
    }
  }
}
