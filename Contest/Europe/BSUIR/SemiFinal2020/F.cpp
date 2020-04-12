#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 998244353;
constexpr int kRoot = 3;
constexpr int kN = 1048576;

int fpow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) res = 1LL * res * a % kMod;
    a = 1LL * a * a % kMod;
    n >>= 1;
  }
  return res;
}

template <int Mod, int Root, int kN>
struct NumTheoreticTrans {
  vector<int> omega;
  NumTheoreticTrans() {
    omega.resize(kN + 1);
    long long x = fpow(Root, (Mod - 1) / kN);
    omega[0] = 1;
    for (int i = 1; i <= kN; ++i) {
      omega[i] = 1LL * omega[i - 1] * x % Mod;
    }
  }

  void Bitrev(vector<int> &v, int n) {
    int z = __builtin_ctz(n) - 1;
    for (int i = 0; i < n; ++i) {
      int x = 0;
      for (int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
      if (x > i) swap(v[x], v[i]);
    }
  }

  void Trans(vector<int> &v, int n) {
    Bitrev(v, n);
    for (int s = 2; s <= n; s <<= 1) {
      int z = s >> 1;
      for (int i = 0; i < n; i += s) {
        for (int k = 0; k < z; ++k) {
          int x = 1LL * v[i + k + z] * omega[kN / s * k] % Mod;
          v[i + k + z] = (v[i + k] + Mod - x) % Mod;
          (v[i + k] += x) %= Mod;
        }
      }
    }
  }

  void InvTrans(vector<int> &v, int n) {
    Trans(v, n);
    for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
    const int inv = fpow(n, Mod - 2);
    for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * inv % Mod;
  }

  vector<int> Multiply(vector<int> a, vector<int> b) {
    int sz = 1, n = a.size(), m = b.size();
    while (sz < n + m - 1) sz <<= 1;
    a.resize(sz, 0), b.resize(sz, 0);
    Trans(a, sz), Trans(b, sz);
    vector<int> c(sz);
    for (int i = 0; i < sz; ++i) c[i] = 1LL * a[i] * b[i] % Mod;
    InvTrans(c, sz);
    c.resize(n + m - 1);
    return c;
  }
};


int main() {
  int n, d, k;
  cin >> n >> d >> k;
  NumTheoreticTrans<kMod, kRoot, kN> ntt;
  vector<int> fc(n + 1, 1), iv(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kMod;
  }
  iv[n] = fpow(fc[n], kMod - 2);
  for (int i = n - 1; i >= 0; --i) iv[i] = 1LL * iv[i + 1] * (i + 1) % kMod;
  int kp = 1;
  vector<int> a(d);
  vector<int> b(n + 1);
  for (int i = 0; i < d; ++i) {
    a[i] = 1LL * kp * iv[i] % kMod;
    kp = 1LL * kp * k % kMod;
  }
  k = n - k;
  kp = 1;
  for (int i = 0; i <= n; ++i) {
    b[i] = 1LL * kp * iv[i] % kMod;
    kp = 1LL * kp * k % kMod;
  }
  vector<int> res = ntt.Multiply(a, b);
  const int kJ = fpow(n, kMod - 2);
  int np = fpow(fpow(n, d), kMod - 2);
  for (int m = d; m <= n; ++m) {
    int p = 1LL * res[m] * fc[m] % kMod;
    p = 1LL * p * np % kMod;
    cout << p << "\n";
    np = 1LL * np * kJ % kMod;
  }
  return 0;
}
