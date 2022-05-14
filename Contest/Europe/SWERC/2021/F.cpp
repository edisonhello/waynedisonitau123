#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N, a, b;
    cin >> N >> a >> b;
    a--;
    b--;
    vector<int> p(N);
    for (int i = 0; i < N; ++i) {
      cin >> p[i];
    }
    vector<int> dist(N, -1);
    vector<int> que = {a};
    dist[a] = 0;

    vector<vector<int>> tree1(N * 4);
    vector<vector<int>> tree2(N * 4);

    auto Insert1 = [&](int x) {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
        tree1[o].push_back(x);
        if (r - l == 1) {
          return;
        }
        int m = (l + r) >> 1;
        if (x < m) {
          dfs(dfs, l, m, o * 2 + 1);
        } else {
          dfs(dfs, m, r, o * 2 + 2);
        }
      };

      return dfs(dfs, 0, N);
    };

    auto Insert2 = [&](int ql, int qr, int x) {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
        if (l >= qr || ql >= r) {
          return;
        }
        if (l >= ql && r <= qr) {
          tree2[o].push_back(x);
          return;
        }
        int m = (l + r) >> 1;
        dfs(dfs, l, m, o * 2 + 1);
        dfs(dfs, m, r, o * 2 + 2);
      };
      return dfs(dfs, 0, N);
    };

    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
      return p[i] < p[j];
    });
    for (int u : order) {
      Insert1(u);
    }
    reverse(order.begin(), order.end());
    for (int u : order) {
      Insert2(max(0, u - p[u]), min(N, u + p[u] + 1), u);
    }

    auto Query1 = [&](int ql, int qr, int v) {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) -> int {
        if (l >= ql && r <= qr) {
          int t = -1;
          while (!tree1[o].empty() && dist[tree1[o].back()] != -1) {
            tree1[o].pop_back();
          }
          if (!tree1[o].empty() && p[tree1[o].back()] >= v) {
            t = tree1[o].back();
          }
          return t;
        }
        if (l >= qr || ql >= r) {
          return -1;
        }
        int m = (l + r) >> 1;
        return max(dfs(dfs, l, m, o * 2 + 1), dfs(dfs, m, r, o * 2 + 2));
      };

      return dfs(dfs, 0, N);
    };

    auto Query2 = [&](int x) {
      auto dfs = [&](auto dfs, int l, int r, int o = 0) -> int {
        int t = -1;
        while (!tree2[o].empty() && dist[tree2[o].back()] != -1) {
          tree2[o].pop_back();
        }
        if (!tree2[o].empty() && p[tree2[o].back()] <= p[x]) {
          t = tree2[o].back();
        }
        if (r - l == 1) {
          return t;
        }
        int m = (l + r) >> 1;
        if (x < m) {
          t = max(t, dfs(dfs, l, m, o * 2 + 1));
        } else {
          t = max(t, dfs(dfs, m, r, o * 2 + 2));
        }
        return t;
      };

      return dfs(dfs, 0, N);
    };

    for (int it = 0; it < que.size(); ++it) {
      int x = que[it];
      while (true) {
        auto t = Query1(max(0, x - p[x]), min(N, x + p[x] + 1), p[x]);
        if (t == -1) {
          break;
        }
        dist[t] = dist[x] + 1;
        que.push_back(t);
      }
      while (true) {
        auto t = Query2(x);
        if (t == -1) {
          break;
        }
        dist[t] = dist[x] + 1;
        que.push_back(t);
      }
    }
    cout << dist[b] << "\n";
  }
}

