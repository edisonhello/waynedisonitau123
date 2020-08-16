#include <bits/stdc++.h>
using namespace std;

int main() {
  int l, r, k, n;
  cin >> l >> r >> k >> n;
  constexpr int kMod = 1'000'000'000 + 7;
 
  vector<int> v;
  const int kM = r - l + 1;
  int tl = -1, tr = -1;
  for (int i = l; i <= r; ++i) {
    if (i % n == 0) {
      if (tl == -1) tl = i / n;
      tr = i / n;
    }
  }

  vector<int> cnt(kM + 1);
  for (int i = 1; i <= kM; ++i) {
    cnt[i] = tr / i - (tl + i - 1) / i + 1;
  }

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kMod;
      a = 1LL * a * a % kMod;
      n >>= 1;
    }
    return res;
  };

  for (int i = 1; i <= kM; ++i) {
    cnt[i] = (fpow(cnt[i], k) + kMod - cnt[i]) % kMod;
  }
  for (int i = kM; i > 0; --i) {
    for (int j = i + i; j <= kM; j += i) {
      (cnt[i] += kMod - cnt[j]) %= kMod;
    }
  }
  int res = cnt[1];
  if (n >= l && n <= r) {
    (res += 1) %= kMod;
  }
  cout << res << "\n";
}
