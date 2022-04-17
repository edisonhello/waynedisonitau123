#include <bits/stdc++.h>
using namespace std;

int64_t pw(int64_t b, int64_t n) {
  int64_t a = 1;
  while (n) {
    if (n & 1) a *= b;
    b *= b;
    n >>= 1;
  }
  return a;
}

int64_t solve() {

  int64_t n, k; 
  cin >> n >> k;

  if (k == 1 || k >= 30) {
    return n;
  } else {
    int64_t sum = 0;
    for (int64_t i = 1; pw(i, k) <= 1'000'000'000; ++i) {
      auto l = pw(i, k), r = pw(i + 1, k) - 1;
      if (l > n) break;
      r = min(r, int64_t(n));
      sum += (r / i) - (l - 1) / i;
    }

    return sum;

  }
}

int main() {
  int t; cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";
    cout << solve() << '\n';
  }
}

