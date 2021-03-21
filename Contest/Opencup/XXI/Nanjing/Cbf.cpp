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

      auto Eval = [&](int down, int up) {
        int64_t dist = static_cast<int64_t>(abs(down)) + up - down;
        int L = kC, R = -kC;
        for (int i = 0; i < N; ++i) {
          if (x[i] < down || x[i] > up) {
            L = min(L, y[i]);
            R = max(R, y[i]);
          }
        }
        if (L != kC) dist += static_cast<int64_t>(min(abs(L), abs(R))) + R - L;
        return dist;
      };

      // auto DivideConquer = [&](auto dfs, int l, int r) -> int64_t {
      //   if (l > r) return kInf;
      //   int m = (l + r) >> 1;
      //   int64_t res = kInf;
      //   int h = -1;
      //   for (int i = 0; i < U.size(); ++i) {
      //     if (U[i] >= D[m]) {
      //       int64_t dist = Eval(D[m], U[i]);
      //       if (dist < res) {
      //         res = dist;
      //         h = i;
      //       }
      //     }
      //   }
      //   res = min(res, dfs(dfs, l, m - 1));
      //   res = min(res, dfs(dfs, m + 1, r));
      //   return res;
      // };

      // return DivideConquer(DivideConquer, 0, D.size() - 1);
      cerr << "D = ";
      for (int d : D) cerr << d << " "; cerr << endl;
      cerr << "U = ";
      for (int u : U) cerr << u << " "; cerr << endl;
      int64_t ans = kInf;
      for (int i = 0; i < D.size(); ++i) {
        int64_t res = kInf;
        int h = -1;
        for (int j = 0; j < U.size(); ++j) {
          int64_t v = Eval(D[i], U[j]);
          if (v < res) {
            res = v;
            h = j;
          }
        }
        ans = min(ans, res);
        cerr << h << " ";
      }
      cerr << endl;
      return ans;
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
