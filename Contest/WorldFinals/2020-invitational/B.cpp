#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  vector<set<pair<int, int>>> tree(N * 4);

  auto Insert = [&](int p, int v, int w) {
    // cout << "Insert l = " << w << " r = " << v << endl;
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      tree[o].insert(make_pair(v, w));
      if (r - l == 1) {
        return;
      }
      int m = (l + r) >> 1;
      if (p < m) dfs(dfs, l, m, o * 2 + 1);
      else dfs(dfs, m, r, o * 2 + 2);
    };

    return dfs(dfs, 0, N);
  };

  auto Erase = [&](int p, int v, int w) {
    // cout << "Erase l = " << w << " r = " << v << endl;
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      tree[o].erase(make_pair(v, w));
      if (r - l == 1) {
        return;
      }
      int m = (l + r) >> 1;
      if (p < m) dfs(dfs, l, m, o * 2 + 1);
      else dfs(dfs, m, r, o * 2 + 2);
    };

    return dfs(dfs, 0, N);
  };

  vector<int> points;

  auto Query = [&](int ql, int qr, int lb, int ub) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      if (l >= qr || ql >= r) return;
      if (l >= ql && r <= qr) {
        auto iter = tree[o].lower_bound(make_pair(lb, -1));
        while (iter != tree[o].end() && iter->first < ub) {
          points.push_back(iter->second);
          iter++;
        }
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
    };

    return dfs(dfs, 0, N);
  };

  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  auto Merge = [&](int x, int y) {
    // cout << "Merge x = " << x << " y = " << y << endl;
    x = Find(x);
    y = Find(y);
    uf[x] = y;
  };

  vector<int> nxt(N);
  for (int i = 0; i < N; ++i) {
    nxt[i] = i;
  }

  while (M--) {
    int e, u, v;
    cin >> e >> u >> v;
    u--;
    v--;
    if (e == 1) {
      if (u > v) swap(u, v);
      if (Find(u) == Find(v)) {
        continue;
      }
      points.clear();
      Query(u + 1, v, v + 1, u + N);
      Query(v + 1, N, u + N + 1, v + N);
      Query(0, u, u + 1, v);
      Merge(u, v);
      for (int p : points) {
        Merge(u, p);
      }
      points.push_back(u);
      points.push_back(v);
      int K = points.size();
      for (int i = 0; i < K; ++i) {
        // cout << "p = " << points[i] << endl;
        assert(points[i] < N);
        if (nxt[points[i]] != points[i]) {
          points.push_back(nxt[points[i]] % N);
        }
      }
      sort(points.begin(), points.end());
      points.resize(unique(points.begin(), points.end()) - points.begin());
      for (int i = 0; i + 1 < points.size(); ++i) {
        if (nxt[points[i]] == points[i] || nxt[points[i]] > points[i + 1]) {
          if (nxt[points[i]] != points[i]) {
            Erase(points[i], nxt[points[i]], points[i]);
          }
          nxt[points[i]] = points[i + 1];
          Insert(points[i], nxt[points[i]], points[i]);
        }
      }
      if (points.size() >= 2) {
        if (nxt[points.back()] == points.back() || nxt[points.back()] > points[0] + N) {
          if (nxt[points.back()] != points.back()) {
            Erase(points.back(), nxt[points.back()], points.back());
          }
          nxt[points.back()] = points[0] + N;
          Insert(points.back(), nxt[points.back()], points.back());
        }
      }
    } else {
      cout << (Find(u) == Find(v));
    }
  }
  cout << "\n";
  return 0;
}
