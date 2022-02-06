#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> a(N), k(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> k[i];
  }

  vector<int> ds(a.begin(), a.end());
  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
  const int M = ds.size();

  struct Node {
    int left, right;
    int64_t tag;

    Node() : left(-1), right(-1), tag(0) {}
  };

  vector<Node> tree;
  tree.reserve(30000000);

  auto NewNode = [&](int z = -1) -> int {
    tree.emplace_back();
    if (z != -1) {
      tree.back() = tree[z];
    }
    return tree.size() - 1;
  };

  vector<int> roots(N + 1);

  auto Build = [&]() {
    auto dfs = [&](auto dfs, int l, int r) -> int {
      int z = NewNode();
      if (r - l == 1) {
        return z; 
      }
      int m = (l + r) >> 1;
      tree[z].left = dfs(dfs, l, m);
      tree[z].right = dfs(dfs, m, r);
      return z;
    };

    return dfs(dfs, 0, M);
  };

  auto Push = [&](int o) {
    if (tree[o].tag != 0) {
      tree[o].left = NewNode(tree[o].left);
      tree[o].right = NewNode(tree[o].right);
      tree[tree[o].left].tag += tree[o].tag;
      tree[tree[o].right].tag += tree[o].tag;
      tree[o].tag = 0;
    }
  };

  auto Query = [&](int p, int x, int y) {
    auto dfs = [&](auto dfs, int l, int r, int x, int y) -> int {
      if (r <= p) {
        return NewNode(x);
      }
      if (l >= p) {
        return NewNode(y);
      }
      int z = NewNode();
      Push(x);
      Push(y);
      int m = (l + r) >> 1;
      tree[z].left = dfs(dfs, l, m, tree[x].left, tree[y].left);
      tree[z].right = dfs(dfs, m, r, tree[x].right, tree[y].right);
      return z;
    };

    return dfs(dfs, 0, M, x, y);
  };

  auto Update = [&](int ql, int qr, int o, int64_t v) {
    auto dfs = [&](auto dfs, int l, int r, int o) -> void {
      if (l >= qr || ql >= r) {
        return;
      }
      if (l >= ql && r <= qr) {
        tree[o].tag += v;
        return;
      }
      // Push(o);
      int m = (l + r) >> 1;
      dfs(dfs, l, m, tree[o].left);
      dfs(dfs, m, r, tree[o].right);
    };

    return dfs(dfs, 0, M, o);
  };

  roots[N] = Build();
  for (int i = N - 1; i >= 0; --i) {
    int p = lower_bound(ds.begin(), ds.end(), a[i]) - ds.begin();
    roots[i] = Query(p + 1, roots[min(N, i + k[i])], roots[i + 1]);

    Update(p + 1, M, roots[i], a[i]);
    Update(0, p + 1, roots[i], 1LL * a[i] * k[i]);
  }

  auto Dfs = [&](int o) {
    auto dfs = [&](auto dfs, int l, int r, int o) -> int64_t {
      if (o == -1) {
        return 0;
      }
      if (r - l == 1) {
        return tree[o].tag;
      }
      int m = (l + r) >> 1;
      return max(dfs(dfs, l, m, tree[o].left), dfs(dfs, m, r, tree[o].right)) + tree[o].tag;
    };

    return dfs(dfs, 0, N, o);
  };

  cout << Dfs(roots[0]) << "\n";
  return 0;
}

