#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int mod = 1000000007;

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod;
    n >>= 1;
  }
  return a;
}

int32_t main() {
  int n, m, k, r, c;
  cin >> n >> m >> k >> r >> c;
  int a1, a2, b1, b2;
  cin >> a1 >> a2 >> b1 >> b2;
  if (a1 == b1 && a2 == b2) {
    cout << pw(k, n * m) << endl;
  } else {
    cout << pw(k, n * m - r * c) << endl;
  }

}
