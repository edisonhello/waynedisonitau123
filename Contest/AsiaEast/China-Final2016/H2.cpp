#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    cout << "Case #" << i + 1 << ": ";
    constexpr int kMod = 1'000'000'000 + 7;

    auto fpow = [&](int a, int n) {
      int res = 1;
      while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
      }
      return res;
    };

    int N, M, K;
    cin >> N >> M >> K;
    int res = 0;
    for (int v = 1; v <= K; ++v) {
      int ways = 1LL * fpow(v - 1, N + M - 2) * fpow(K, N * M - N - M + 1) % kMod;
      (res += ways) >= kMod ? res -= kMod : 0;
    }
    res = 1LL * res * N * M % kMod;
    (res += fpow(K, N * M)) >= kMod ? res -= kMod : 0;
    cout << res << "\n";
  }
}
