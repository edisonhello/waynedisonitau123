#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> x(N), y(N);
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i];

    auto Solve = [&]() {
      vector<int> D = {0}, U = {0};
      for (int i = 0; i < N; ++i) {
        if (x[i] < 0) D.push_back(x[i]);
        if (x[i] > 0) U.push_back(x[i]);
      }
      sort(D.begin(), D.end());
      D.resize(unique(D.begin(), D.end()) - D.begin());
      sort(U.begin(), U.end());
      U.resize(unique(U.begin(), U.end()) - U.begin());

      constexpr int64_t kInf = 1'000'000'000'000'000'000;
      constexpr int kC = 2'000'000'000;

      vector<pair<int, int>> p(N);
      for (int i = 0; i < N; ++i) p[i] = make_pair(x[i], y[i]);
      sort(p.begin(), p.end());
      
      vector<int> PMax(N), PMin(N), SMax(N), SMin(N);
      for (int i = 0; i < N; ++i) {
        PMax[i] = PMin[i] = p[i].second;
        if (i > 0) {
          PMax[i] = max(PMax[i], PMax[i - 1]);
          PMin[i] = min(PMin[i], PMin[i - 1]);
        }
      }
      for (int i = N - 1; i >= 0; --i) {
        SMax[i] = SMin[i] = p[i].second;
        if (i + 1 < N) {
          SMax[i] = max(SMax[i], SMax[i + 1]);
          SMin[i] = min(SMin[i], SMin[i + 1]);
        }
      }

      auto Eval = [&](int down, int up) {
        int64_t dist = static_cast<int64_t>(abs(down)) + up - down;
        int L = kC, R = -kC;
        auto it = lower_bound(p.begin(), p.end(), make_pair(down, -kC));
        if (it != p.begin()) {
          L = min(L, PMin[it - p.begin() - 1]);
          R = max(L, PMax[it - p.begin() - 1]);
        }
        it = upper_bound(p.begin(), p.end(), make_pair(up, kC));
        if (it != p.end()) {
          L = min(L, SMin[it - p.begin()]);
          R = max(R, SMax[it - p.begin()]);
        }
        if (L != kC) dist += static_cast<int64_t>(min(abs(L), abs(R))) + R - L;
        return dist;
      };

      auto DivideConquer = [&](auto dfs, int l, int r, int tl, int tr) -> int64_t {
        if (l > r) return kInf;
        int m = (l + r) >> 1;
        int64_t res = kInf;
        int h = -1;
        for (int i = tl; i <= tr; ++i) {
          if (U[i] >= D[m]) {
            int64_t dist = Eval(D[m], U[i]);
            if (dist < res) {
              res = dist;
              h = i;
            }
          }
        }
        res = min(res, dfs(dfs, l, m - 1, h, tr));
        res = min(res, dfs(dfs, m + 1, r, tl, h));
        return res;
      };

      return DivideConquer(DivideConquer, 0, D.size() - 1, 0, U.size() - 1);
    };

    int64_t ans = Solve();
    for (int i = 0; i < N; ++i) x[i] = -x[i];
    ans = min(ans, Solve());
    for (int i = 0; i < N; ++i) {
      x[i] = -x[i];
      swap(x[i], y[i]);
    }
    ans = min(ans, Solve());
    for (int i = 0; i < N; ++i) x[i] = -x[i];
    ans = min(ans, Solve());
    cout << ans << "\n";
  }
  return 0;
}
