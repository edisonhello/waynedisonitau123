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

    if (n == 3) { cout << "No" << '\n'; return; }

    for (int i = 0; i < n; ++i) {
      vector<int> djs(n);
      iota(djs.begin(), djs.end(), 0);

      function<int(int)> F = [&] (int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); };
      auto U = [&] (int x, int y) { djs[F(x)] = F(y); };

      for (auto [u, v] : e) {
        if (u == i || v == i) continue;
        U(u, v);
      }

      set<int> st;
      for (int j = 0; j < n; ++j) if (i != j) st.insert(F(j));

      if (st.size() > n / 2) {
        cout << "No" << '\n';
        return;
      }
    }

    cout << "Yes" << '\n';
}

int main() {
  int t; cin >> t; while (t--) {
    solve();
  }
}
