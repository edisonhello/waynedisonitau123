#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int mod = 998244353;

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = a * b % mod;
    b = b * b % mod;
    n >>= 1;
  }
  return a;
}

int inv(int x) { return pw(x, mod - 2); }

int C(int n, int m) {
  int a = 1;
  for (int i = 0; i < m; ++i) a = a * (n - i) % mod;
  for (int i = 1; i <= m; ++i) a = a * inv(i) % mod;
  return a;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    if (n == 1 && m == 1) {
      cout << 1 << '\n';
      continue;
    }

    if (n == 1 || m == 1) {
      n = n + m - 1;
      int ans = 2 + C(n - 2, 2);
      cout << ans % mod << '\n';
      continue;
    }

    auto put1 = [&]() {
      int ans = 1;
      if (n > 1) ans *= 2;
      if (m > 1) ans *= 2;
      return ans % mod;
    };

    auto put2 = [&]() {
      int ans = 0;
      if (n > 2) ans += C((n - 2) * 2, 2);
      if (m > 2) ans += C((m - 2) * 2, 2);
      return ans % mod;
    };

    auto put3 = [&, n = n - 2, m = m - 2]() {
      int ans = 0;

      auto f1 = [&](int n, int m) {
        int ans = n * n % mod * m % mod * (m + 1) % mod * (2 * m + 1) % mod *
                      inv(6) % mod -
                  n * m % mod * (m + 1) % mod * inv(2) % mod -
                  m * C(n, 2) % mod;
        return (ans % mod + mod) % mod;
      };

      auto f2 = [&](int n, int m) {
        int ans = n * n % mod * max(int(0), m - 1) % mod * max(int(0), m - 2) % mod -
                  n * n % mod * max(int(0), m - 2) % mod;
        return (ans % mod + mod) % mod;
      };

      ans += 4 * n * n % mod * m % mod * m % mod;
      ans += 2 * (f1(n, m) + f1(m, n)) % mod;
      ans += 2 * (f2(n, m) + f2(m, n)) % mod;
      return ans % mod;
    };

    auto put4 = [&]() { return C((n - 2) * (m - 2) % mod, 4); };

    int p1 = put1();
    int p2 = put2();
    int p3 = put3();
    int p4 = put4();
    // cout << "p 1 2 3 4 " << p1 << ' ' << p2 << ' ' << p3 << ' ' << p4 << endl;
    int ans = (p1 + p2 + p3 + p4) % mod;

    cout << ans << '\n';
  }
}

