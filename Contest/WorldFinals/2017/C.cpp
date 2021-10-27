#include <bits/stdc++.h>
using namespace std;

int main() {
  int R, C;
  cin >> R >> C;
  vector<vector<int>> A(R, vector<int>(C));
  vector<int> row(R), col(C);
  int64_t ans = 0;
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      cin >> A[i][j];
      if (A[i][j] > 0) {
        ans += A[i][j] - 1;
      }
      row[i] = max(row[i], A[i][j]);
      col[j] = max(col[j], A[i][j]);
    }
  }

  vector<int> ds(row.begin(), row.end());
  ds.insert(ds.end(), col.begin(), col.end());
  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

  int64_t res = 0;
  for (int d : ds) {
    if (d == 0) continue;
    vector<int> rows, cols;
    for (int i = 0; i < R; ++i) {
      if (row[i] == d) {
        rows.push_back(i);
      }
    }
    for (int i = 0; i < C; ++i) {
      if (col[i] == d) {
        cols.push_back(i);
      }
    }

    if (rows.empty() || cols.empty()) {
      res += 1LL * (d - 1) * (cols.size() + rows.size());
      continue;
    }
    vector<vector<int>> g(rows.size());
    for (int i = 0; i < rows.size(); ++i) {
      for (int j = 0; j < cols.size(); ++j) {
        if (A[rows[i]][cols[j]] > 0) {
          g[i].push_back(j);
        }
      }
    }
    vector<bool> vis(cols.size());
    vector<int> match(cols.size(), -1);
    int m = 0;

    auto Dfs = [&](auto dfs, int x) -> bool {
      for (int y : g[x]) {
        if (!vis[y]) {
          vis[y] = true;
          if (match[y] == -1 || dfs(dfs, match[y])) {
            match[y] = x;
            return true;
          }
        }
      }
      return false;
    };

    for (int i = 0; i < g.size(); ++i) {
      fill(vis.begin(), vis.end(), false);
      m += Dfs(Dfs, i);
    }

    int cnt = rows.size() + cols.size() - m;
    res += 1LL * cnt * (d - 1);
  }
  cout << ans - res << "\n";
}

