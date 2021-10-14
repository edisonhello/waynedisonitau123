#include <bits/stdc++.h>
using namespace std;

constexpr int kP = 998244353;

int fpow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) res = 1LL * res * a % kP;
    a = 1LL * a * a % kP;
    n >>= 1;
  }
  return res;
}

int main() {
  int N, K;
  cin >> N >> K;
  int ans = 1;
  for (int i = 1; i <= K - 1; ++i) {
    ans = 1LL * ans * i % kP;
  }
  ans = fpow(ans, kP - 2);
  for (int i = 0; i < K - 1; ++i) {
    ans = 1LL * ans * (N - 1 - i) % kP;
  }
  int phi = 1;
  for (int p = 2; 1LL * p * p <= N; ++p) {
    if (N % p == 0) {
      int f = 1;
      while (N % p == 0) {
        N /= p;
        f *= p;
      }
      phi *= (f / p) * (p - 1);
    }
  }
  if (N > 1) {
    phi *= N - 1;
  }
  cout << 1LL * ans * phi % kP << "\n";
}
