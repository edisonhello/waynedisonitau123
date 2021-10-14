#include <bits/stdc++.h>
using namespace std;

int main() {
  int p, q, r;
  int64_t L, R;
  cin >> p >> q >> r >> L >> R;
  int t = p * r + q * r + p * q;
  if (t > p * q * r) {
    cout << "0\n";
    return 0;
  }
  constexpr int kC = 2'000'000;
  if (t < p * q * r) {
    int64_t ans = 0;
    for (int i = 0; i < kC; ++i) {
      if (L + i > R) break;
      int64_t N = L + i;
      if ((N + p - 1) / p + (N + q - 1) / q + (N + r - 1) / r <= N) ans++;
    }
    if (R - L + 1 > kC) ans += R - L + 1 - kC;
    cout << ans << "\n";
  } else {
    int lc = lcm(lcm(p, q), r);
    int64_t ans = R / lc - (L - 1) / lc;
    cout << ans << "\n";
  }
  return 0;
}
