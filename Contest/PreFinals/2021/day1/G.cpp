#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;

  constexpr int kP = 1'000'000'000 + 7;

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kP;
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  int ans = 1;
  for (int i = 0; i < N; ++i) {
    ans = 1LL * ans * ((1LL * K * N + kP - i) % kP) % kP;
    ans = 1LL * ans * fpow(N - i, kP - 2) % kP;
  }
  int d = (1LL * (K - 1) * N + 1) % kP;
  cout << 1LL * ans * fpow(d, kP - 2) % kP << "\n";
}
