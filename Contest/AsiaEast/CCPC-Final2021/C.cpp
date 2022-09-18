#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> t(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    cin >> t[i];
  }
  constexpr int kP = 998244353;

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) {
        res = 1LL * res * a % kP;
      }
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  vector<int> fc(N + 2, 1), iv(N + 2, 1);
  for (int i = 1; i <= N + 1; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  auto Bin = [&](int n, int k) -> int {
    if (n < k || k < 0) {
      return 0;
    }
    return 1LL * fc[n] * iv[k] % kP * iv[n - k] % kP;
  };

  int ans = 1;
  for (int i = 0; i < N - 2; ++i) {
    ans = 1LL * ans * Bin(t[i + 1] + 1, t[i]) % kP; 
  }
  cout << ans << "\n";
  return 0;
}
