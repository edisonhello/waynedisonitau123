#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> p(n + 5);
    vector<vector<int>> g(n + 5);
    for (int i = 2; i <= n; ++i) {
      cin >> p[i];
      g[p[i]].push_back(i);
    }

    vector<int> dep(n + 5, 0);
    auto dfs1 = [&](auto dfs1, int now) -> void {
      for (int i : g[now]) {
        dep[i] = dep[now] + 1;
        dfs1(dfs1, i);
      }
    };
    dfs1(dfs1, 1);

    if (k == 1) {
      cout << 0 << '\n';
      cout << 1 << '\n';
      continue;
    }

    int x = -1;
    for (int i = 2; i <= n; ++i) {
      if (dep[i] + 1 <= k && (x == -1 || dep[i] > dep[x])) x = i;
    }

    vector<int> tag(n + 5, 0);
    for (int xx = x; xx != 1; xx = p[xx]) {
      tag[xx] = 1;
    }

    int other = k - 1 - dep[x];
    assert(other >= 0);

    // cerr << "x = " << x << " other = " << other << endl;

    vector<int> path;
    auto dfs2 = [&] (auto dfs2, int now) -> void {
      path.push_back(now);
      for (int i : g[now]) {
        if (tag[i]) continue;
        if (other > 0) {
          dfs2(dfs2, i);
          path.push_back(now);
        }
      }

      for (int i : g[now]) if (tag[i]) {
        dfs2(dfs2, i);
      }
    };

    dfs2(dfs2, 1);

    cout << path.size() - 1 << '\n';
    for (int i : path) cout << i << ' ';
    cout << '\n';
  }
}
