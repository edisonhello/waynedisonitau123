#include <bits/stdc++.h>
#define double long double
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  vector<double> s(n);
  for (int i = 0; i < n; ++i) cin >> s[i];
  vector<double> ans(n);

  auto Choose = [&](int a, int b) -> double {
    if (b > a) return 0;
    assert(n - k >= b);
    double res = 1.0;
    for (int i = 0; i < b; ++i) {
      res *= (a - i);
      res /= (n - i);
      res /= (b - i);
      res *= (n - k - i);
    }
    for (int i = b; i < n - k; ++i) {
      res /= (n - i);
      res *= (n - k - i);
    }
    return res;
  };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int cnt = j - i;
      if (cnt < 0) cnt += n;
      if (cnt > n - k) continue;
      int r = n - (cnt + 1);
      int h = n - k - cnt;
      double p = Choose(r, h);
      ans[j] += p * s[i];
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << fixed << setprecision(20) << ans[i] << " ";
  }
  cout << "\n";
}
