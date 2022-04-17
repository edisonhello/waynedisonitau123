#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

constexpr int pp = 131, pp2 = 97;
constexpr int mod = 998244353, mod2 = 1000'000'007;

int pppw[1000006], pp2pw[1000006], fac[1000006], ifac[1000006];

int hh[1000006], hh2[1000006];
unordered_set<uint64_t> hhcnthhst;
cc_hash_table<int64_t, int> hhcnt;

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = 1ll * a * b % mod;
    b = 1ll * b * b % mod;
    n >>= 1;
  }
  return a;
}

int inv(int x) { return pw(x, mod - 2); }

void init() {
  pppw[0] = 1;
  for (int i = 1; i <= 1000000; ++i) pppw[i] = 1ll * pppw[i - 1] * pp % mod;
  pp2pw[0] = 1;
  for (int i = 1; i <= 1000000; ++i) pp2pw[i] = 1ll * pp2pw[i - 1] * pp2 % mod2;

  fac[0] = 1;
  for (int i = 1; i <= 1000000; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
  ifac[1000000] = inv(fac[1000000]);
  for (int i = 999999; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;

  // hhcnthhst.reserve(200006);
  // hhcnt.reserve(200006);
}

int solve() {
  string s; 
  cin >> s;
  int n = s.size();

  for (int i = 0; i < n; ++i) {
    hh[i + 1] = (1ll * hh[i] * pp + s[i]) % mod;
    hh2[i + 1] = (1ll * hh2[i] * pp2 + s[i]) % mod2;
  }

  auto GetHH = [&](int l, int r) {
    int64_t h1 = (hh[r + 1] - 1ll * pppw[r - l + 1] * hh[l] % mod + mod) % mod;
    int64_t h2 = (hh2[r + 1] - 1ll * pp2pw[r - l + 1] * hh2[l] % mod2 + mod2) % mod2;
    return (h1 << 32 | h2);
  };

  int64_t ans = 0;
  uint64_t hhcnthh = 0;
  auto AddHash = [&](uint64_t hh) {
    int &cnt = hhcnt[hh];
    ++cnt;
    hhcnthh ^= hh ^ 880301 ^ (0xdeadbeef) ^ ((hh + 87) * (cnt + 99));
  };
  auto RemoveHash = [&](uint64_t hh) {
    int &cnt = hhcnt[hh];
    hhcnthh ^= hh ^ 880301 ^ (0xdeadbeef) ^ ((hh + 87) * (cnt + 99));
    --cnt;
  };

  vector<pair<uint64_t, int>> vals;

  for (int wid = 1; wid <= n; ++wid) {
    if (wid > n / 2) {
      if (GetHH(0, wid - 1) == GetHH(n - wid, n - 1)) ++ans;
      else ans += 2;
      continue;
    }

    // clear
    hhcnthhst.clear();
    hhcnt.clear();
    vals.clear();

    // init
    int nseg = n / wid;
    for (int i = 0; i + wid - 1 < n; i += wid) {
      AddHash(GetHH(i, i + wid - 1));
    }

    // calc perm
    int ways = fac[nseg];
    for (auto [_h, cnt] : hhcnt) {
      ways = 1ll * ways * ifac[cnt] % mod;
    }
    vals.emplace_back(hhcnthh, ways);
    // hhcnthhst.insert(hhcnthh);
    // ans += ways;

    for (int emp = n / wid * wid, empe = n - 1; emp > 0; ) {
      int64_t hh = GetHH(emp - wid, emp - 1);
      int cc = hhcnt[hh];
      // assert(cc >= 1);
      ways = 1ll * ways * fac[cc] % mod * ifac[cc - 1] % mod;
      RemoveHash(hh);

      hh = GetHH(empe - wid + 1, empe);
      cc = hhcnt[hh];
      ways = 1ll * ways * fac[cc] % mod * ifac[cc + 1] % mod;
      AddHash(hh);

      vals.emplace_back(hhcnthh, ways);
      // if (hhcnthhst.count(hhcnthh) == 0) {
      //   hhcnthhst.insert(hhcnthh);
      //   ans += ways;
      // }

      emp -= wid;
      empe -= wid;
    }

    sort(vals.begin(), vals.end());
    for (int i = 0; i < (int)vals.size(); ++i) {
      if (i == 0 || vals[i].first != vals[i - 1].first) ans += vals[i].second;
    }
  }

  return ans % mod;
}

int main() {
  init();
  int t; cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": " << solve() << '\n';
  }
}

