#include <bits/stdc++.h>
using namespace std;

const int mod = 1'000'000'007;

int cnt[1000006];
int fac[1000006];

int main() {
  fac[0] = 1;
  for (int i = 1; i <= 1000'000; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
  }

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int m; cin >> m;

  int64_t tot = 0;
  for (int i = 1; i <= m; ++i) {
    int c;
    cin >> c;
    ++cnt[c];
    tot += c;
  }

  int val = 0, way = 1;
  for (int i = 1000'000; i >= 1; --i) {
    int r = cnt[i];
    if (r == 0) continue;
    if (i >= 2) {
      cnt[i - 2] += r;
      way = 1ll * way * fac[r] % mod * fac[r] % mod;
      (val += 1ll * (i - 1) * ((tot - r) % mod) % mod * r % mod) %= mod;
      tot -= r * 2;
      assert(tot >= 0);
      // std::cerr << "way " << way << std::endl;
      // std::cerr << "mul " << 
    } else if (i == 1) {
      way = 1ll * way * fac[r] % mod;
      tot -= r;
    }
  }

  cout << val << ' ' << way << endl;

}

