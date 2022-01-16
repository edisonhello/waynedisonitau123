#include <bits/stdc++.h>
using namespace std;

constexpr int p = 131;
constexpr int mod = 1000000007;

int hh[1000006], pp[1000006];
int cnt[1000006];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  string s;
  cin >> s;
  int n = s.size();

  for (int i = 1; i <= n; ++i) {
    hh[i] = (1ll * hh[i - 1] * p + s[i - 1]) % mod;
  }

  pp[0] = 1;
  for (int i = 1; i <= n; ++i) pp[i] = 1ll * pp[i - 1] * p % mod;

  auto gethash = [&](int l, int r) {
    return (hh[r] - 1ll * hh[l - 1] * pp[r - l + 1] % mod + mod) % mod;
  };

  // vector<int> all;
  for (int i = 1; i < n; ++i) {
    cnt[i] = cnt[i - 1];
    if (gethash(1, n - i) == gethash(1 + i, n)) {
      // all.push_back(i);
      cnt[i]++;
    }
  }
  cnt[n] = cnt[n - 1];

  int q; cin >> q;
  while (q--) {
    int x;
    cin >> x;
    int l = max(x - 1, n - x);
    cout << cnt[n] - cnt[l] << '\n';

  }
}



