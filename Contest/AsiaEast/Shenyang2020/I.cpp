#include <bits/stdc++.h>
using namespace std;

int64_t Euclid(int64_t a, int64_t b, int64_t c, int64_t n) {
  if (a >= c || b >= c) {
    return (a / c) * (n * (n + 1) / 2) + (b / c) * (n + 1) +
           Euclid(a % c, b % c, c, n);
  }
  if (n < 0 || a == 0) return 0;
  int64_t m = (a * n + b) / c;
  return n * m - Euclid(c, c - b - 1, a, m - 1);
}

int64_t Solve(int H, int M, int64_t A) {
  int U = -1;
  for (int bit = 30; bit >= 0; --bit) {
    if (U + (1 << bit) < H) {
      int64_t t = (A + 1LL * M * (U + (1 << bit))) / (H - 1) + 1;
      if (t <= M) U += (1 << bit);
    }
  }
  int L = -1;
  for (int bit = 30; bit >= 0; --bit) {
    if (L + (1 << bit) < H) {
      if (A + 1LL * M * (L + (1 << bit)) < 0) L += (1 << bit);
    }
  }
  L++;
  // if (L > U) return 0;
  int64_t ans = U - L + 1;
  ans += Euclid(M, A + 1LL * M * L, H - 1, U - L);
  ans += 1LL * (H - 1 - U) * M;
  return ans;
}

int main() {
  int H, M;
  int64_t A;
  cin >> H >> M >> A;
  if (A * 2 == 1LL * H * M) {
    cout << 1LL * H * M << "\n";
    return 0;
  }
  int64_t ans = Solve(H, M, A) - Solve(H, M, -A - 1) +
                Solve(H, M, 1LL * H * M + A) -
                Solve(H, M, 1LL * H * M - A - 1) +
                Solve(H, M, -1LL * H * M + A) - Solve(H, M, -1LL * H * M - A - 1);
  cout << ans << "\n";
}
