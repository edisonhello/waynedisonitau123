#include <bits/stdc++.h>
using namespace std;

int main() {
  constexpr int kM = 4'000'000;
  constexpr int kMod = 1'000'000'000 + 7;
  vector<int> fc(kM + 1, 1), iv(kM + 1);
  for (int i = 1; i <= kM; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kMod;
  }

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kMod;
      a = 1LL * a * a % kMod;
      n >>= 1;
    }
    return res;
  };

  iv[kM] = fpow(fc[kM], kMod - 2);
  for (int i = kM - 1; i >= 0; --i) {
    iv[i] = 1LL * iv[i + 1] * (i + 1) % kMod;
  }

  vector<int> pfc(kM + 1, 1), piv(kM + 1, 1);
  for (int i = 1; i <= kM; ++i) {
    pfc[i] = 1LL * pfc[i - 1] * fc[i] % kMod; 
    piv[i] = 1LL * piv[i - 1] * iv[i] % kMod;
  }

  int t;
  cin >> t;

  auto Solve = [&](int n, int m, int x, int y) {
    int a = 1LL * pfc[n + m + x + y - 1] * piv[n + m + x + y - 1 - min(n, m)] % kMod;
    int b = 1LL * pfc[x + y + min(n, m) - 1];
    if (x + y > 0) b = 1LL * b * piv[x + y - 1] % kMod;
    int res = 1LL * a * fpow(b, kMod - 2) % kMod;
    return res;
  };

  while (t--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a = a - b + 1;
    c = c - d + 1;
    if (a < c || a == c && b < d) {
      swap(a, c);
      swap(b, d);
    }
    if (b >= d) {
      // int res = 1LL * pfc[a + b - 1] * piv[min(a, b) - 1] % kMod * piv[a + b - 1 - min(a, b)] % kMod;
      // res = 1LL * fc[a * b] * fpow(res, kMod - 2) % kMod;
      // cout << res << "\n";
      cout << 1LL * fc[a * b] * fpow(Solve(a, b, 0, 0), kMod - 2) % kMod << "\n";
    } else {
      int res = 1LL * Solve(c, b, a - c, d - b) * Solve(a - c, b, 0, 0) % kMod * Solve(c, d - b, 0, 0) % kMod;
      res = 1LL * fc[a * b + c * d - c * b] * fpow(res, kMod - 2) % kMod;
      cout << res << "\n";
    }
  }
  return 0;
}
