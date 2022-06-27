#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);
    vector<int> uf(N), ed(N), sz(N, 1);
    iota(uf.begin(), uf.end(), 0);

    function<int(int)> Find = [&](int a) {
      if (a == uf[a]) {
        return a;
      }
      return uf[a] = Find(uf[a]);
    };

    for (int i = 0; i < M; ++i) {
      int a, b;
      cin >> a >> b;
      a--;
      b--;
      g[a].push_back(b);
      g[b].push_back(a);
      a = Find(a);
      b = Find(b);
      if (a != b) {
        uf[a] = b;
        sz[b] += sz[a];
        ed[b] += ed[a];
      }
      ++ed[b];
    }

    vector<int> color(N, -1);

    auto Dfs = [&](auto dfs, int x, int c) -> bool {
      color[x] = c;
      for (int u : g[x]) {
        if (color[u] == -1) {
          if (!dfs(dfs, u, c ^ 1)) {
            return false;
          }
        } else {
          if (color[u] != (c ^ 1)) {
            return false;
          }
        }
      }
      return true;
    };

    vector<bool> vis(N);
    int sum = 0;
    for (int i = 0; i < N; ++i) {
      if (!vis[Find(i)]) {
        vis[Find(i)] = true;
        if (Dfs(Dfs, i, 0)) {
          sum += ed[Find(i)] - sz[Find(i)] + 1;
        } else {
          sum += ed[Find(i)] - sz[Find(i)];
        }
      }
    }
    constexpr int kP = 998244353;
    int ans = 1;
    for (int i = 0; i < sum; ++i) {
      ans = 5LL * ans % kP;
    }
    cout << ans << "\n";
  }
}
