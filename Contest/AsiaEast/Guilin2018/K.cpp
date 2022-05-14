#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N, L, m;
    cin >> N >> L >> m;
    vector<int> vec(N);
    for (int i = 0; i < N; ++i) {
      cin >> vec[i];
    }
    vector<vector<int>> sp(1, vec);
    for (int i = 1; (1 << i) <= N; ++i) {
      sp.emplace_back(N);
      for (int j = 0; j + (1 << i) <= N; ++j) {
        sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
      }
    }

    auto Query = [&](int l, int r) {
      int p = 31 - __builtin_clz(r - l + 1);
      return min(sp[p][l], sp[p][r - (1 << p) + 1]);
    };

    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    vector<int64_t> dp(N, -kInf);
    vector<int64_t> nxt(N);

    int t = vec[0];
    int64_t ans = 0;
    for (int i = 1; i < N; ++i) {
      dp[i] = vec[i] - t;
      t = min(t, vec[i]);
      ans = max(ans, dp[i]);
    }

    auto DivideConquer = [&](auto self, int l, int r, int tl, int tr) -> void {
      if (l > r) {
        return;
      }
      int m = (l + r) >> 1;
      int64_t best = -kInf;
      int opt = tl;
      for (int i = tl; i <= min(m - 2, tr); ++i) {
        if (m - i <= L) {
          int t = Query(i + 1, m - 1);
          if (dp[i] - t + vec[m] > best) {
            best = dp[i] - t + vec[m];
            opt = i;
          }
        }
      }
      nxt[m] = best;
      self(self, l, m - 1, tl, opt);
      self(self, m + 1, r, opt, tr);
    };

    for (int i = 2; i <= m; ++i) {
      DivideConquer(DivideConquer, 0, N - 1, 0, N - 1);
      ans = max(ans, *max_element(nxt.begin(), nxt.end()));
      dp.swap(nxt);
    }
    cout << "Case " << tc << ": " << ans << "\n";
  }
}

