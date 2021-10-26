#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int N, M;
  cin >> N >> M;
  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<int> nxt(N);
  for (int i = 0; i < N; ++i) nxt[i] = i;
  vector<int> tree(N * 4, -1);

  vector<set<int>> vc(N);
  for (int i = 0; i < N; ++i) {
    vc[i].insert(i);
  }

  auto Update = [&](int ql, int qr, int v) -> void {
    // cout << "Update ql = " << ql << " qr = " << qr << " v = " << v << endl;
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      if (l >= qr || ql >= r) return;
      if (l >= ql && r <= qr) {
        tree[o] = max(tree[o], v);
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
    };

    return dfs(dfs, 0, N);
  };

  auto Query = [&](int p) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> int {
      if (r - l == 1) {
        return tree[o];
      }
      int m = (l + r) >> 1;
      if (p < m) {
        return max(tree[o], dfs(dfs, l, m, o * 2 + 1));
      } else {
        return max(tree[o], dfs(dfs, m, r, o * 2 + 2));
      }
    };

    return dfs(dfs, 0, N);
  };

  auto Merge = [&](int x, int y) {
    // cout << "Merge x = " << x << " y = " << y << endl;
    x = Find(x);
    y = Find(y);
    if (x == y) {
      return;
    }
    if (vc[x].size() > vc[y].size()) {
      swap(x, y);
    }
    for (int p : vc[x]) {
      auto iter = vc[y].lower_bound(p); 
      if (iter != vc[y].end()) {
        if (p + 1 <= *iter - 1) {
          Update(p + 1, *iter, p);
        }
      }
      if (iter != vc[y].begin()) {
        if (*prev(iter) + 1 <= p - 1) {
          Update(*prev(iter) + 1, p, *prev(iter));
        }
      }
      vc[y].insert(p);
    }
    if (vc[y].size() > 2) {
      int a = *vc[y].begin(), b = *vc[y].rbegin();
      if (b + 1 <= a + N - 1) {
        Update(b + 1, N, b);
        Update(0, a, b);
      }
    }
    uf[x] = y;
  };

  for (int i = 0; i < M; ++i) {
    int e, u, v;
    cin >> e >> u >> v;
    u--;
    v--;
    if (u > v) {
      swap(u, v);
    }
    if (e == 1) {
      vector<int> vec;
      int x = v;
      while (true) {
        int p = Query(x);
        if (p == -1) break;
        vec.push_back(p);
        x = p;
      }
      x = u;
      while (true) {
        int p = Query(x);
        if (p == -1) break;
        vec.push_back(p);
        x = p;
      }
      for (int x : vec) {
        Merge(u, x);
      }
      Merge(u, v);
    } else {
      cout << (Find(u) == Find(v));
    }
  }
  cout << "\n";
  return 0;
}
