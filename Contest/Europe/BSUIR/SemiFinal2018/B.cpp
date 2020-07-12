#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  int a, b;
  cin >> a >> b;
  vector<vector<int>> g(n, vector<int>(m));
  vector<pair<int, int>> z;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> g[i][j];
      if (g[i][j] == 0) {
        z.emplace_back(i, j);
      }
    }
  }
  vector<bitset<1000>> ba(m);
  vector<bitset<1000>> bb(m);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (g[j][i] == a) {
        ba[i].set(j);
      }
      if (g[j][i] == b) {
        bb[i].set(j);
      }
    }
  }
  vector<vector<int>> g1(2 * z.size());
  vector<vector<int>> g2(2 * z.size());

  auto AddEdge = [&](int a, int b) {
    g1[a].push_back(b);
    g2[b].push_back(a);
  };
  bitset<1000> va, vb;
  for (int i = 0; i < z.size(); ++i) {
    int x = z[i].first, y = z[i].second;
    va.reset();
    vb.reset();
    for (int j = 0; j < m; ++j) {
      if (j == y) continue;
      if (g[x][j] == a) va |= ba[j];
      if (g[x][j] == b) vb |= bb[j];
    }
    bool aa = false, bb = false;
    for (int j = 0; j < n; ++j) {
      if (j == x) continue;
      if (g[j][y] == a && va[j]) aa = true;
      if (g[j][y] == b && vb[j]) bb = true;
    }
    if (aa && bb) {
      cout << "No\n";
      return 0;
    }
    if (aa) {
      AddEdge(i, i + z.size());
    }
    if (bb) {
      AddEdge(i + z.size(), i);
    }
  }

  for (int i = 0; i < z.size(); ++i) {
    for (int j = i + 1; j < z.size(); ++j) {
      int x1, y1, x2, y2;
      tie(x1, y1) = z[i];
      tie(x2, y2) = z[j];
      if (g[x1][y2] == g[x2][y1]) {
        if (g[x1][y2] == a) {
          AddEdge(i, j + z.size());
          AddEdge(j, i + z.size());
        } else if (g[x2][y1] == b) {
          AddEdge(i + z.size(), j);
          AddEdge(j + z.size(), i);
        }
      }
    }
  }
  vector<bool> v(2 * z.size());
  vector<int> scc(2 * z.size(), -1);
  vector<int> ord;

  auto Dfs = [&](auto dfs, int x) -> void {
    v[x] = true;
    for (int u : g1[x]) {
      if (!v[u]) {
        dfs(dfs, u);
      }
    }
    ord.push_back(x);
  };

  auto Dfs2 = [&](auto dfs, int x, int p) -> void {
    scc[x] = p;
    for (int u : g2[x]) {
      if (scc[u] == -1) {
        dfs(dfs, u, p);
      }
    }
  };

  for (int i = 0; i < 2 * z.size(); ++i) {
    if (!v[i]) {
      Dfs(Dfs, i);
    }
  }
  int p = 0;
  for (int i = ord.size() - 1; i >= 0; --i) {
    if (scc[ord[i]] == -1) {
      Dfs2(Dfs2, ord[i], p++);
    }
  }
  for (int i = 0; i < z.size(); ++i) {
    if (scc[i] == scc[i + z.size()]) {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
  vector<int> res(p, -1);
  for (int i = ord.size() - 1; i >= 0; --i) {
    int x = ord[i];
    if (res[scc[x]] != -1) continue;
    int y = x >= z.size() ? x - z.size() : x + z.size();
    res[scc[x]] = 0;
    res[scc[y]] = 1;
  }
  for (int i = 0; i < z.size(); ++i) {
    if (res[scc[i]] == 1) {
      g[z[i].first][z[i].second] = a;
    } else {
      g[z[i].first][z[i].second] = b;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) cout << g[i][j] << " ";
    cout << "\n";
  }
  return 0;
}
