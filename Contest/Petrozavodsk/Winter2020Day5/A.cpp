#include <bits/stdc++.h>
using namespace std;

int used[1005];
int possible[1005];

int main() {
  int m, n; cin >> m >> n;

  vector<vector<int>> v(n, vector<int>(m, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> v[i][j];
    }
  }

  auto dfs = [&] (auto dfs, int tev, int evs) -> void {
    if (tev == n) return;
    for (int i = 0; i < n; ++i) if (!(evs & (1 << i))) {
      for (int j = 0; j < m; ++j) if (!used[v[i][j]]) {
        used[v[i][j]] = 1;
        possible[v[i][j]] = 1;

        dfs(dfs, tev + 1, evs | (1 << i));

        used[v[i][j]] = 0;
        break;
      }
    }
  };

  dfs(dfs, 0, 0);

  vector<int> ans;
  for (int i = 1; i <= 1000; ++i) if (possible[i]) ans.push_back(i);

  cout << ans.size() << endl;
  for (int i : ans) cout << i << ' ';
  cout << endl;
}
