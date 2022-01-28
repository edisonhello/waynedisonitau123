#include <bits/stdc++.h>
using namespace std;

int fac[1000006];
int ifac[1000006];
int iinv[1000006];


int main() {
  int n, p; cin >> n >> p;

  auto pw = [&](int b, int n) {
    int a = 1;
    while (n) {
      if (n & 1) a = 1ll * a * b % p;
      b = 1ll * b * b % p;
      n >>= 1;
    }
    return a;
  };
  auto inv = [&](int x) { return pw(x, p - 2); };

  fac[0] = 1;
  for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % p;
  ifac[n] = inv(fac[n]);
  for (int i = n - 1; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % p;
  for (int i = 1; i <= n; ++i) iinv[i] = ifac[i] * 1ll * fac[i - 1] % p;

  vector<int> cnt(n * 2, 0);
  vector<int> ans(n + 5, 0);

  auto dfs = [&](auto dfs, int len, int sum, int64_t prod, int inv, int prev) -> bool {
    // cout << "dfs " << len << ' ' << sum << ' ' << prod << ' ' << inv << endl;
    if (sum <= prod) {
      int64_t ones = prod - sum;
      int64_t totlen = len + ones;
      if (totlen > n) return false;
      // cout << "len " << len << " sum " << sum << " prod " << prod << " totlen " << totlen << endl;

      int ways = fac[totlen] * 1ll * inv % p;
      // cout << "inv = " << inv << ", ways = " << ways << endl;
      ans[totlen] += 1ll * ways * ifac[ones] % p;
      if (ans[totlen] >= p) ans[totlen] -= p;
    }

    for (int put = prev; put <= n; ++put) {
      ++cnt[put];
      int ninv = 1ll * inv * iinv[cnt[put]] % p;
      int ret = dfs(dfs, len + 1, sum + put, prod * put, ninv, put);
      --cnt[put];

      if (!ret) break;
    }
    return true;
  };

  dfs(dfs, 0, 0, 1, 1, 2);

  for (int i = 2; i <= n; ++i) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}

