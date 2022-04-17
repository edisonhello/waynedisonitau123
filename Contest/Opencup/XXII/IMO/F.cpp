#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int pw(int b, int n, int m) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % m;
    b = 1ll * b * b % m;
    n >>= 1;
  }
  return a;
}

int inv(int x, int m) {
  return pw(x, m - 2, m);
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int p, q; cin >> p >> q;

  while (q--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if ((a + b) % p != (c + d) % p) {
      cout << -1 << '\n';
      continue;
    }

    int k = (a + b) % p;
    int ik = inv(k, p);

    c %= p;

    for (int step = 0; step <= 30; ++step) {
      int64_t mul = (1ll << step);
      int64_t frn = a * mul % p;

      // frn - c = ?k

      int q = 1ll * (frn - c + p) % p * ik % p;

      if (q < mul) {
        cout << step << '\n';
        break;
      } 
    }
  }


}

