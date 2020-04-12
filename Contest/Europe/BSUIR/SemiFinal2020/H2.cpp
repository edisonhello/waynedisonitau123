#include <bits/stdc++.h>
using namespace std;

constexpr int kA = 500;
constexpr int kB = 1000000 + 1;
array<int, kB> dp, fr;

int main() {
  fill(dp.begin(), dp.end(), 1e9);
  dp[0] = 0;
  for (int i = 1; i < kB; ++i) {
    for (int j = 1; j <= kA && i >= j * (j - 1); ++j) {
      if (dp[i - j * (j - 1)] + j < dp[i]) {
        dp[i] = dp[i - j * (j - 1)] + j;
        fr[i] = j;
      }
    }
  }

  auto Solve = [&](int x, int y, int up) {
    if (y == 1) {
      return true;
      cout << 1 << "\n";
      cout << 2 * x << "\n";
      // return 0;
    }
    if (y % 2 == 0) {
      return false;
      cout << "-1\n";
      // return 0;
    }
    for (int b = 1; b < up; ++b) {
      int64_t v = 1LL * b * y;
      if (v % (2 * x) == 0) {
        int64_t a = v / (2 * x) + 1;
        if (a % 2 == 0 && dp[b] <= a && a <= 10000) {
          vector<int> v;
          for (int i = 0; i < a - dp[b]; ++i) v.push_back(1);
          while (b > 0) {
            v.push_back(fr[b]);
            b -= fr[b] * (fr[b] - 1);
          }
          return true;
          cout << v.size() << "\n";
          for (int u : v) cout << u << " ";
          cout << "\n";
          // return 0;
        }
      }
    }
    return false;
    cout << "-1\n";
  };

  for (int x = 1; x <= 1000; ++x) {
    for (int y = 1; y <= 1000; ++y) {
      if (__gcd(x, y) != 1) continue;
      if (Solve(x, y, kB) != Solve(x, y, kB / 2)) {
        cout << "x = " << x << " y = " << y << endl;
        return 0;
      }
    }
  }
  // int x, y;
  // cin >> x >> y;
  // int g = __gcd(x, y);
  // x /= g;
  // y /= g;
  return 0;
}
