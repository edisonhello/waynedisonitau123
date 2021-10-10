#include <bits/stdc++.h>
using namespace std;



int main() {
  int n, m; cin >> n >> m;
  vector<pair<int, int>> edges;
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    edges.emplace_back(u, v);
  }

  int mx = n + 1;
  set<int> st;

  for (int z = 1; z < (1 << m); ++z) {
    vector<int> in(n), out(n);
    bool no = 0;
    int ue = 0;
    for (int i = 0; i < m; ++i) if (z & (1 << i)) {
      ++ue;
      auto [u, v] = edges[i];
      if (out[u] || in[v]) no = 1;
      out[u] = in[v] = 1;
    }
    int fly = -1;
    for (int i = 0; i < n; ++i) {
      if (!in[i]) ++fly;
    }

    if (fly < mx) {
      mx = fly;
    }
  }
}
