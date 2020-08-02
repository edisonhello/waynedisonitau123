#include <bits/stdc++.h>
using namespace std;

int main() {
  int s, d, t;
  cin >> s >> d >> t;
  int n;
  cin >> n;
  vector<int> l(n), r(n);
  vector<int> p = {0};
  for (int i = 0; i < n; ++i) {
    cin >> l[i] >> r[i];
    p.push_back(l[i]);
    p.push_back(r[i]);
  }
  p.push_back(s);

  auto Between = [&](int x, int l, int r) {
    if (r >= l) return x >= l && x <= r;
    return x <= l || x >= r;
  };

  vector<int64_t> dp(p.size());
  for (int i = 1; i < p.size(); ++i) {
    int pos = p[i];
    dp[i] = 1'000'000'000'000'000'000;
    bool ok = true;
    for (int j = i - 1; j >= 0; --j) {
      int target = p[j];
      for (int g = 0; g < n; ++g) {
        if (l[g] >= target && r[g] <= pos) {
          int tl = l[g] % d, tr = (r[g] % d + d - 1) % d;
          if (Between(pos % d, tl, tr)) {
            ok = false;
            break;
          }
        }
      }
      if (ok) {
        int nxt = (target % d <= pos % d) ? (target / d) * d + pos % d : (target / d + 1) * d + pos % d;
        assert(pos >= nxt);
        assert(nxt >= target);
        dp[i] = min(dp[i], dp[j] + (nxt - target) + int64_t((pos - nxt) / d) * t);
      } else {
        if (
      }
    }
    cout << "dp[" << p[i] << "] = " << dp[i] << endl;
  }
  cout << dp.back() << "\n";
}
