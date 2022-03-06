#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int pw(int b, int n, int a = 1) {
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod;
    n >>= 1;
  }
  return a;
}

int inv(int x) { return pw(x, mod - 2); }

int n;

int ABC(int sab, int c) {
  static int rec[400005];
  static int vis[400005];

  if (c >= 2) return 0;
  if (sab + 4 * c >= n) return 0;

  if (vis[sab]) return rec[sab];
  vis[sab] = 1;

  return rec[sab] = ((0ll + ABC(sab + 1, c) + ABC(sab + 3, c) + ABC(sab, c + 1)) * inv(3) + 1) % mod;
}

int BC(int b, int c) {
  if (2 * (b + c) >= n) return 0;

  if (c >= 2) {
    static int rec[400005];
    static int vis[400005];

    int s = b + c;
    if (vis[s]) return rec[s];
    vis[s] = 1;
    return rec[s] = ((0ll + 0 + BC(b + 1, c) + BC(b, c + 1)) * inv(3) + 1) % mod;
  } else { // c == 1
    static int rec[400005];
    static int vis[400005];

    if (vis[b]) return rec[b];
    vis[b] = 1;
    rec[b] = ((0ll + ABC(b * 3, c) + BC(b + 1, c) + BC(b, c + 1)) * inv(3) + 1) % mod;

    // cout << "BC c = 1 b = " << b << " ans " << rec[b] << endl;

    return rec[b];
  }
}

int AC(int a, int c) {
  static int rec[400005];
  static int vis[400005];

  assert(a > 0);
  if (c >= 2) return 0;
  if (a >= n - 1) return 0;
  if (vis[a]) return rec[a];

  vis[a] = 1;
  rec[a] = ((0ll + AC(a + 1, c) + ABC((a - 1) + 3, c) + AC(a, c + 1)) * inv(3) + 1) % mod;

  // cout << "AC a " << a << " c " << c << " ans " << rec[a] << endl;
  return rec[a];
}

int AB(int s) {
  static int rec[400005];
  static int vis[400005];

  if (vis[s]) return rec[s];
  if (s >= n) return 0;

  vis[s] = 1;
  return rec[s] = ((0ll + AB(s + 1) + AB(s + 3) + ABC(s, 1)) * inv(3) + 1) % mod;
}

int C(int c) {
  static int rec[400005];
  static int vis[400005];

  if (c >= max(n, 3)) {
    return 3ll * inv(2) % mod;
  }
  if (vis[c]) return rec[c];

  vis[c] = 1;
  rec[c] = ((0ll + AC(1, c) + BC(1, c) + C(c + 1)) * inv(3) + 1) % mod;

  // cout << "C c = " << c << " ans " << rec[c] << endl;

  return rec[c];
}

int B(int b) {
  static int rec[400005];
  static int vis[400005];

  if (vis[b]) return rec[b];
  if (b >= (n + 1) / 2) return 0;

  vis[b] = 1;
  rec[b] = ((0ll + B(b + 1) + AB(3 * b) + BC(b, 1)) * inv(3) + 1) % mod;

  // cout << "B b = " << b << " ans " << rec[b] << endl;

  return rec[b];
}

int A(int a) {
  static int rec[400005];
  static int vis[400005];

  if (vis[a]) return rec[a];
  if (a >= n + 1) return 0;

  vis[a] = 1;
  rec[a] = ((0ll + A(a + 1) + AB(a + 2) + AC(a, 1)) * inv(3) + 1) % mod;

  // cout << "A a = " << a << " ans " << rec[a] << endl;

  return rec[a];
}

int O() {
  return ((0ll + A(1) + B(1) + C(1)) * inv(3) + 1) % mod;
}

int main() {
  cin >> n;

  cout << O() << endl;
}


