#include <bits/stdc++.h>
using namespace std;

bool is_scc(auto g, auto ig) {
  int n = g.size(); 

  vector<int> tp;
  vector<bool> vis(n);

  

  for (int i = 0; i < n; ++i) if (!vis[i]) dfs(i);
}

void solve() {
  int n; cin >> n;
  vector<vector<int>> v(n, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> v[i][j];
  vector<tuple<int, int, int>> oedges;
  for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
    if (v[i][j] == 0) oedges.emplace_back(j, i, v[j][i]);
    else oedges.emplace_back(i, j, v[i][j]);
  }
  int en = (int)oedges.size();
  int min_co = INT_MAX;
  vector<pair<int, int>> min_co_w;
  for (int z = 0; z < (1 << en); ++z) {
    int co = 0;
    vector<vector<int>> g(n), ig(n);
    vector<pair<int, int>> co_w;
    for (int i = 0; i < en; ++i) {
      auto [u, v, w] = oedges[i];
      if (z & (1 << i)) {
        co += w;
        co_w.emplace_back(u, v);
        swap(u, v);
      }
      g[u].push_back(v);
      ig[v].push_back(u);
    }

    if (is_scc(g, ig)) {
      if (co < min_co) {
        min_co = co;
        min_co_w.swap(co_w);
      }
    }
  }

  if (min_co != INT_MAX) {
    cout << "YES" << endl;
    cout << min_co_w.size() << endl;
    for (auto [u, v] : min_co_w) cout << u << ' ' << v << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) solve();
}
