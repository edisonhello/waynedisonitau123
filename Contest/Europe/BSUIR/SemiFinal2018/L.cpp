#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  constexpr int kMod = 1'000'000'000 + 7;

  if (n == 1) {
    cout << 1 << endl;
    exit(0);
  }

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) {
        res = 1LL * res * a % kMod;
      }
      a = 1LL * a * a % kMod;
      n >>= 1;
    }
    return res;
  };

  vector<int> pref = {1};
  for (int i = 1; 2 * n - i >= 0; i += 2) {
    pref.push_back(2 * n - i);
  }
  for (int i = 1; i < pref.size(); ++i) {
    pref[i] = 1LL * pref[i] * pref[i - 1] % kMod;
  }

  int ans = 0;
  for (int x = 2 * n + 2; x <= 4 * n; ++x) {
    int ways = ((4 * n + 1) - x) / 2;
    int g = 2 * n - 1 - x / 2;
    int u = fpow(x - 2 * n - 1, g);
    assert(g + 1 < pref.size());
    int d = fpow(pref[g + 1], kMod - 2);
    ans += 1LL * u * d % kMod * ways % kMod;
    ans %= kMod;
  }
  cout << ans << "\n";
}
