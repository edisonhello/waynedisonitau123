#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  vector<int> x1(N), x2(N), y1(N), y2(N);
  constexpr int kC = 2000;
  vector<vector<tuple<int, int, int>>> Lv(kC + 1);
  vector<vector<tuple<int, int, int>>> Rv(kC + 1);
  for (int i = 0; i < N; ++i) {
    cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    Lv[x1[i]].emplace_back(y1[i], y2[i], i);
    Rv[x2[i]].emplace_back(y1[i], y2[i], i);
  }
  vector<set<int>> tree(kC * 4);

  auto Update = [&](int ql, int qr, int p, bool add) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
      if (l >= qr || ql >= r) return;
      if (l >= ql && r <= qr) {
        if (add) tree[o].insert(p);
        else tree[o].erase(p);
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
    };

    return dfs(dfs, 0, kC);
  };

  vector<vector<pair<int, int>>> intv(kC, vector<pair<int, int>>(kC));

  auto Traverse = [&](int p) {
    auto dfs = [&](auto dfs, int l, int r, int x, int y, int o = 0) -> void {
      if (!tree[o].empty()) {
        x = min(x, *tree[o].begin());
        y = max(y, *tree[o].rbegin());
      }
      if (r - l == 1) {
        intv[p][l] = make_pair(x, y);
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, x, y, o * 2 + 1);
      dfs(dfs, m, r, x, y, o * 2 + 2);
    };

    return dfs(dfs, 0, kC, N, -1);
  };

  for (int i = 0; i < kC; ++i) {
    for (auto [l, r, p] : Lv[i]) Update(l, r, p, true);
    for (auto [l, r, p] : Rv[i]) Update(l, r, p, false);
    Traverse(i);
  }
  vector<vector<pair<int, int>>> qr(N);
  for (int i = 0; i < Q; ++i) {
    int L, R;
    cin >> L >> R;
    L--;
    R--;
    qr[R].emplace_back(L, i);
  }
  vector<pair<int, int>> vec;
  int B = 0;
  for (int i = 0; i < kC; ++i) {
    for (int j = 0; j < kC; ++j) {
      if (intv[i][j].second == -1) {
        B++;
        continue;
      }
      vec.push_back(intv[i][j]);
    }
  }
  sort(vec.begin(), vec.end(), [&](const auto &X, const auto &Y) { return X.second < Y.second; });

  vector<int> fenw(N + 1);

  auto Add = [&](int p) {
    for (int i = p + 1; i <= N; i += i & -i) fenw[i]++;
  };

  auto Query = [&](int p) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i) res += fenw[i];
    return res;
  };

  vector<int> ans(Q);
  for (int i = 0, j = 0; i < N; ++i) {
    while (j < vec.size() && vec[j].second <= i) {
      Add(vec[j].first);
      j++;
    }
    for (auto [l, q] : qr[i]) {
      ans[q] = kC * kC - (j - Query(l - 1) + B);
    }
  }
  for (int i = 0; i < Q; ++i) cout << ans[i] << "\n";
  return 0;
}
