#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, K;
  cin >> N >> K;

  constexpr int kP = 998244353;

  vector<vector<int>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    if (x > y) {
      swap(x, y);
    }
    g[y].push_back(x);
  }

  vector<int> dp(N + 1);
  vector<int> nxt(N + 1);
  vector<pair<int, vector<int>>> tree(N * 4);
  vector<int> tag(N * 4);
  dp[0] = 1;

  constexpr int kInf = 1'000'000'000;

  auto Build = [&]() {
    fill(tag.begin(), tag.end(), 0);
    auto dfs = [&](auto self, int l, int r, int o = 0) {
      if (r - l == 1) {
        tree[o].first = kInf;
        tree[o].second.resize(K + 1);
        return;
      }
      int m = (l + r) >> 1;
      self(self, l, m, o * 2 + 1);
      self(self, m, r, o * 2 + 2);
      tree[o].first = min(tree[o * 2 + 1].first, tree[o * 2 + 2].first);
      tree[o].second.resize(K + 1);
    };

    return dfs(dfs, 0, N);
  };

  auto Push = [&](int o) {
    for (int k = 1; k <= 2; ++k) {
      tree[o * 2 + k].first += tag[o];
      tag[o * 2 + k] += tag[o];
    }
    tag[o] = 0;
  };

  auto Update = [&](int ql, int qr, int v) {
    auto dfs = [&](auto self, int l, int r, int o = 0) {
      if (l >= qr || ql >= r) {
        return;
      }
      if (l >= ql && r <= qr) {
        tag[o] += v;
        tree[o].first += v;
        return;
      }
      Push(o);
      int m = (l + r) >> 1;
      self(self, l, m, o * 2 + 1);
      self(self, m, r, o * 2 + 2);
      if (tree[o * 2 + 1].first < tree[o * 2 + 2].first) {
        tree[o] = tree[o * 2 + 1];
      } else if (tree[o * 2 + 1].first > tree[o * 2 + 2].first) {
        tree[o] = tree[o * 2 + 2];
      } else {
        tree[o].first = tree[o * 2 + 1].first;
        for (int i = 0; i <= K; ++i) {
          tree[o].second[i] = (tree[o * 2 + 1].second[i] + tree[o * 2 + 2].second[i]) % kP;
        }
      }
    };

    return dfs(dfs, 0, N);
  };

  auto Set = [&](int p, const vector<int>& d) {
    auto dfs = [&](auto self, int l, int r, int o = 0) {
      if (r - l == 1) {
        tree[o].second = d;
        return;
      }
      Push(o);
      int m = (l + r) >> 1;
      if (p < m) {
        self(self, l, m, o * 2 + 1);
      } else {
        self(self, m, r, o * 2 + 2);
      }
      if (tree[o * 2 + 1].first < tree[o * 2 + 2].first) {
        tree[o] = tree[o * 2 + 1];
      } else if (tree[o * 2 + 1].first > tree[o * 2 + 2].first) {
        tree[o] = tree[o * 2 + 2];
      } else {
        tree[o].first = tree[o * 2 + 1].first;
        for (int i = 0; i <= K; ++i) {
          tree[o].second[i] = (tree[o * 2 + 1].second[i] + tree[o * 2 + 2].second[i]) % kP;
        }
      }
    };

    return dfs(dfs, 0, N);
  };

  Build();
  vector<int> d(K + 1);
  vector<int> nd(K + 1);
  d[0] = 1;
  Set(0, d);
  for (int i = 0; i < N; ++i) {
    Update(i, i + 1, -kInf - i);
    for (int u : g[i]) {
      Update(0, u + 1, -1);
    }
    nd[0] = 0;
    for (int j = 0; j < K; ++j) {
      nd[j + 1] = tree[0].second[j];
    }
    if (i + 1 < N) {
      Set(i + 1, nd);
    } else {
      for (int t = 1; t <= K; ++t) {
        cout << nd[t] << "\n";
      }
    }
  }
  return 0;
}

