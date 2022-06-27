#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Q;
  cin >> N >> Q;
  vector<int> a(N), s(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> s[i];
  }
  vector<int64_t> tree(N * 4);
  vector<int64_t> tag(N * 4);
  vector<int> sum(N * 4);

  auto Build = [&]() {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) {
      if (r - l == 1) {
        tree[o] = a[l];
        sum[o] = s[l];
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
      tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
      sum[o] = sum[o * 2 + 1] + sum[o * 2 + 2];
    };
    return dfs(dfs, 0, N);
  };

  auto Push = [&](int o) {
    for (int k = 1; k <= 2; ++k) {
      tree[o * 2 + k] += tag[o] * sum[o * 2 + k];
      tag[o * 2 + k] += tag[o];
    }
    tag[o] = 0;
  };

  auto Flip = [&](int p) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) {
      if (r - l == 1) {
        sum[o] ^= 1;
        return;
      }
      Push(o);
      int m = (l + r) >> 1;
      if (p < m) dfs(dfs, l, m, o * 2 + 1);
      else dfs(dfs, m, r, o * 2 + 2);
      tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
      sum[o] = sum[o * 2 + 1] + sum[o * 2 + 2];
    };
    return dfs(dfs, 0, N);
  };

  auto Update = [&](int ql, int qr, int v) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) {
      if (l >= qr || ql >= r) {
        return;
      }
      if (l >= ql && r <= qr) {
        tree[o] += 1LL * v * sum[o];
        tag[o] += v;
        return;
      }
      Push(o);
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
      tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
      sum[o] = sum[o * 2 + 1] + sum[o * 2 + 2];
    };
    return dfs(dfs, 0, N);
  };

  auto Query = [&](int ql, int qr) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> int64_t {
      if (l >= qr || ql >= r) {
        return 0;
      }
      if (l >= ql && r <= qr) {
        return tree[o];
      }
      Push(o);
      int m = (l + r) >> 1;
      return dfs(dfs, l, m, o * 2 + 1) + dfs(dfs, m, r, o * 2 + 2);
    };
    return dfs(dfs, 0, N);
  };

  Build();

  while (Q--) {
    int t;
    cin >> t;
    if (t == 1 || t == 2) {
      int x;
      cin >> x;
      Flip(x - 1);
    } else if (t == 3) {
      int l, r, x;
      cin >> l >> r >> x;
      Update(l - 1, r, x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << Query(l - 1, r) << "\n";
    }
  }
}
