#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k, l;
  cin >> n >> k >> l;

  constexpr int kMod = 1'000'000'000 + 7;

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kMod;
      a = 1LL * a * a % kMod;
      n >>= 1;
    }
    return res;
  };

  auto Fac = [&](int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i) {
      res = 1LL * res * i % kMod;
    }
    return res;
  };

  auto Choose = [&](int n, int k) {
    if (n < k) return 0LL;
    return 1LL * Fac(n) * fpow(Fac(n - k), kMod - 2) % kMod * fpow(Fac(k), kMod - 2) % kMod;
  };

  if (l == n) {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
      (res += fpow(k, __gcd(i, n))) >= kMod ? res -= kMod : 0;
    }
    res = 1LL * res * fpow(n, kMod - 2) % kMod;
    cout << res << "\n";
  } else {
    if (l % 2 == 1) {
      int res = (Choose(n + k - 1, k - 1) + Choose(k, n)) % kMod;
      cout << res << "\n";
    } else {
      cout << Choose(n + k - 1, k - 1) << "\n";
    }
  }
}
