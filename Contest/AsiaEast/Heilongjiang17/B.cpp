#include <bits/stdc++.h>
using namespace std;

struct Node {
  int best;
  int best_right;
  int best_left;

  Node operator+(const Node& rhs) const {
    Node res{};
    res.best = max(best, rhs.best);
    res.best = max(res.best, rhs.best_right - best_left);
    res.best_left = min(best_left, rhs.best_left);
    res.best_right = max(best_right, rhs.best_right);
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Q;
  cin >> N >> Q;
  string s;
  cin >> s;
  vector<int> sum(N + 1);
  for (int i = 0; i < N; ++i) {
    sum[i + 1] = sum[i] + (s[i] == '1' ? 1 : -1);
  }

  vector<Node> tree(N * 4);

  auto Build = [&]() {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      if (r - l == 1) {
        tree[o].best = (s[l] == '1' ? 1 : 0);
        tree[o].best_left = sum[l];
        tree[o].best_right = sum[r];
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
      tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
    };

    return dfs(dfs, 0, N);
  };

  Build();

  auto Query = [&](int ql, int qr) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> Node {
      if (l >= ql && r <= qr) {
        return tree[o];
      }
      int m = (l + r) >> 1;
      if (qr <= m) {
        return dfs(dfs, l, m, o * 2 + 1);
      } else if (ql >= m) {
        return dfs(dfs, m, r, o * 2 + 2);
      } else {
        return dfs(dfs, l, m, o * 2 + 1) + dfs(dfs, m, r, o * 2 + 2);
      }
    };

    return dfs(dfs, 0, N);
  };

  int ans = 0;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    l--;
    if (sum[r] - sum[l] == l - r) {
      ans ^= (r - l + 1);
    } else {
      Node res = Query(l, r);
      ans ^= max(0, -(sum[r] - sum[l] - res.best));
    }
  }
  cout << ans << "\n";
}
