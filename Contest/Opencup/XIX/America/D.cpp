#include <bits/stdc++.h>
using namespace std;

int64_t Euclid(int64_t a, int64_t b, int64_t c, int64_t n) {
  if (a >= c || b >= c) {
    return (a / c) * (n * (n + 1) / 2) + (b / c) * (n + 1) +
           Euclid(a % c, b % c, c, n);
  }
  if (n < 0 || a == 0) {
    return 0;
  }
  int64_t m = (a * n + b) / c;
  return n * m - Euclid(c, c - b - 1, a, m - 1);
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int p, q, n;
    cin >> p >> q >> n;
    cout << 1LL * p * n * (n + 1) / 2 - q * Euclid(p, 0, q, n) << "\n";
  }
}
