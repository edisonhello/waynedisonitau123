#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<int> xa(N), ya(N);
  vector<int> xb(M), yb(M);
  vector<int> ys;
  for (int i = 0; i < N; ++i) {
    cin >> xa[i] >> ya[i];
    ys.push_back(ya[i]);
  }
  for (int i = 0; i < M; ++i) {
    cin >> xb[i] >> yb[i];
    ys.push_back(yb[i]);
  }
  sort(ys.begin(), ys.end());
  ys.resize(unique(ys.begin(), ys.end()) - ys.begin());
  vector<int> oa(N);
  iota(oa.begin(), oa.end(), 0);
  vector<int> ob(M);
  iota(ob.begin(), ob.end(), 0);
  sort(oa.begin(), oa.end(), [&](int i, int j) { return xa[i] < xa[j]; });
  sort(ob.begin(), ob.end(), [&](int i, int j) { return xb[i] < xb[j]; });
  int ptr = 0;
  constexpr int64_t kInf = 4'000'000'000;
  vector<int64_t> dist(N, kInf);

  int K = ys.size();
  vector<pair<int64_t, int64_t>> tree(K * 4, make_pair(kInf, kInf));

  auto Update = [&](int p, int64_t x, int64_t y) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) {
      if (r - l == 1) {
        tree[o].first = min(tree[o].first, x);
        tree[o].second = min(tree[o].second, y);
        return;
      }
      int m = (l + r) >> 1;
      if (p < m) {
        dfs(dfs, l, m, o * 2 + 1);
      } else {
        dfs(dfs, m, r, o * 2 + 2);
      }
      tree[o].first = min(tree[o * 2 + 1].first, tree[o * 2 + 2].first);
      tree[o].second = min(tree[o * 2 + 1].second, tree[o * 2 + 2].second);
    };

    return dfs(dfs, 0, K);
  };

  auto Query = [&](int ql, int qr) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> pair<int64_t, int64_t> {
      if (l >= ql && r <= qr) {
        return tree[o];
      }
      int m = (l + r) >> 1;
      if (qr <= m) {
        return dfs(dfs, l, m, o * 2 + 1);
      } else if (ql >= m) {
        return dfs(dfs, m, r, o * 2 + 2);
      } else {
        auto [a, b] = dfs(dfs, l, m, o * 2 + 1);
        auto [c, d] = dfs(dfs, m, r, o * 2 + 2);
        return make_pair(min(a, c), min(b, d));
      }
    };

    return dfs(dfs, 0, K);
  };

  for (int u : oa) {
    while (ptr < M && xb[ob[ptr]] <= xa[u]) {
      int y = lower_bound(ys.begin(), ys.end(), yb[ob[ptr]]) - ys.begin();
      Update(y, yb[ob[ptr]] - xb[ob[ptr]], -yb[ob[ptr]] - xb[ob[ptr]]);
      ptr++;
    }
    int y = lower_bound(ys.begin(), ys.end(), ya[u]) - ys.begin();
    int64_t t = Query(y, ys.size()).first;
    if (t != kInf) {
      dist[u] = min(dist[u], t - ya[u] + xa[u]);
    }
    t = Query(0, y + 1).second;
    if (t != kInf) {
      dist[u] = min(dist[u], t + ya[u] + xa[u]);
    }
  }

  reverse(oa.begin(), oa.end());
  reverse(ob.begin(), ob.end());
  fill(tree.begin(), tree.end(), make_pair(kInf, kInf));
  ptr = 0;
  for (int u : oa) {
    while (ptr < M && xb[ob[ptr]] >= xa[u]) {
      int y = lower_bound(ys.begin(), ys.end(), yb[ob[ptr]]) - ys.begin();
      Update(y, yb[ob[ptr]] + xb[ob[ptr]], -yb[ob[ptr]] + xb[ob[ptr]]);
      ptr++;
    }
    int y = lower_bound(ys.begin(), ys.end(), ya[u]) - ys.begin();
    int64_t t = Query(y, ys.size()).first;
    if (t != kInf) {
      dist[u] = min(dist[u], t - ya[u] - xa[u]);
    }
    t = Query(0, y + 1).second;
    if (t != kInf) {
      dist[u] = min(dist[u], t + ya[u] - xa[u]);
    }
  }
  int64_t sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += dist[i];
  }
  cout << sum << "\n";
  return 0;
}
