#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);  

  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<vector<int>> g(N);
    for (int i = 0; i < N - 1; ++i) {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    vector<int> min_leaf_down(N, N);
    vector<int> min_leaf(N);
    vector<int> to(N, -1);

    auto DfsDown = [&](auto dfs, int x, int p = -1) -> void {
      for (int u : g[x]) {
        if (u == p) continue;
        dfs(dfs, u, x);
        min_leaf_down[x] = min(min_leaf_down[x], min_leaf_down[u]);
      } 
      if (min_leaf_down[x] == N) {
        min_leaf_down[x] = x;
      }
    };

    auto DfsUp = [&](auto dfs, int x, int p = -1, int f = -1) -> void {
      pair<int, int> max_leaf = {f, p};
      set<int> l;
      if (f != -1) l.insert(f);
      for (int u : g[x]) {
        if (u == p) continue;
        max_leaf = max(max_leaf, make_pair(min_leaf_down[u], u));
        l.insert(min_leaf_down[u]);
      }
      if (max_leaf.first > x) {
        to[x] = max_leaf.second;
      }
      for (int u : g[x]) {
        if (u == p) continue;
        l.erase(min_leaf_down[u]);
        int t = l.empty() ? -1 : *l.begin();
        dfs(dfs, u, x, t);
        l.insert(min_leaf_down[u]);
      }
    };

    DfsDown(DfsDown, 0);
    DfsUp(DfsUp, 0);

    int x = -1;
    for (int i = 0; i < N; ++i) {
      if (g[i].size() == 1) {
        if (x == -1) {
          x = i;
          break;
        }
      }
    }

    x = g[x][0];

    while (to[x] != -1) {
      x = to[x];
    }

    vector<deque<int>> ans(N);

    auto DfsAns = [&](auto dfs, int x, int p = -1) -> void {
      vector<int> child;
      for (int u : g[x]) {
        if (u == p) continue;
        dfs(dfs, u, x);
        child.push_back(u);
      }

      sort(child.begin(), child.end(), [&](int i, int j) {
        return ans[i][0] < ans[j][0];
      });

      for (int u : child) {
        if (ans[u].size() > ans[x].size()) {
          ans[u].swap(ans[x]);
          while (!ans[u].empty()) {
            ans[x].push_front(ans[u].back());
            ans[u].pop_back();
          }
        } else {
          for (int v : ans[u]) {
            ans[x].push_back(v);
          }
        }
      }
      ans[x].push_back(x);
    };

    DfsAns(DfsAns, x);
    for (int u : ans[x]) cout << u + 1 << " ";
    cout << "\n";
  }
}

