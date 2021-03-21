#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> e;
    for (int i = 0; i < m; ++i) {
      int u, v; cin >> u >> v;
      --u, --v;
      e.emplace_back(u, v);
    }

    for (int z = 0; z < (1 << m); ++z) {
      if (__builtin_popcount(z) != n - 1) continue;

      vector<int> djs(n);
      iota(djs.begin(), djs.end(), 0);

      function<int(int)> F = [&] (int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); };
      auto U = [&] (int x, int y) { djs[F(x)] = F(y); };

      bool bad = 0;

      vector<int> deg(n, 0);
      for (int i = 0; i < m; ++i) if (z & (1 << i)) {
        int u = e[i].first, v = e[i].second;
        if (F(u) == F(v)) { bad = 1; break; }

        U(e[i].first, e[i].second);
        ++deg[e[i].first];
        ++deg[e[i].second];
      }

      for (int i = 1; i < n; ++i) {
        if (F(0) != F(i)) { bad = 1; break; }
      }

      for (int i = 0; i < n; ++i) {
        if (deg[i] > n / 2) { bad = 1; break; }
      }

      if (!bad) {
        cout << "Yes" << '\n';
        return;
      }
    }
    cout << "No" << '\n';
}

int main() {
  int t; cin >> t; while (t--) {
    solve();
  }
}
