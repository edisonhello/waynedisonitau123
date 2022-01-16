#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

/*
namespace fft {

constexpr int kN = 262144;
constexpr int kP = 998244353;
constexpr int kRoot = 3;
int omega[kN + 1];

void Init() {
  int x = fpow(kRoot, (kP - 1) / kN);
  omega[0] = 1;
  for (int i = 1; i <= kN; ++i) {
    omega[i] = 1LL * omega[i - 1] * x % kP;
  }
}

void BitReverse(vector<int>& v, int n) {
  int z = __builtin_clz(n) - 1;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    for (int j = 0; j <= z; ++j) {
      x ^= (i >> j & 1) << (z - j);  
    }
    if (x > i) {
      swap(v[x], v[i]);
    }
  }
}

void Transform(vector<int>& v, int n) {
  BitReverse(v, n);
  for (int s = 2; s <= n; s <<= 1) {
    int z = s >> 1;
    for (int i = 0; i < n; i += s) {
      for (int k = 0; k < z; ++k) {
        int x = 1LL * v[i + k + z] * omega[kN / s * k] % kP;
        v[i + k + z] = (v[i + k] + kP - x) % kP;
        v[i + k] = (v[i + k] + x) % kP;
      }
    }
  }
}

int fpow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) res = 1LL * res * a % kP;
    a = 1LL * a * a % kP;
    n >>= 1;
  }
  return res;
}

void InvTransform(vector<int>& v, int n) {
  Transform(v, n);
  for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
  const int kI = fpow(n, kP - 2);
  for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * kI % kP;
}

}  // namespace fft
*/

int main() {
  int N, M, K;
  cin >> N >> M >> K;
  if (N < M || M < K) {
    cout << "0\n";
    return 0;
  }
  if (K == 0) {
    if (M == 0) {
      cout << "1\n";
    } else {
      cout << "0\n";
    }
    return 0;
  }
  constexpr int kP = 998244353;
  vector<int> fc(N + 1, 1), iv(N + 1, 1);

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kP;
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  for (int i = 1; i <= N; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  auto Bin = [&](int n, int k) -> int {
    if (n < k || k < 0) return 0;
    return 1LL * fc[n] * iv[k] % kP * iv[n - k] % kP;
  };

  auto Solve = [&](int k) {
    if (k == 0) {
      if (M == 0) return 1;
      return 0;
    }
    int ans = 0;
    for (int i = 0; N >= 1LL * k * i && M >= 1LL * k * i; ++i) {
      int ways = 1LL * Bin(N - M + 1, i) * Bin(N - k * i, M - k * i) % kP;
      if (i & 1) ans += kP - ways;
      else ans += ways;
      ans %= kP;
    }
    return ans;
  };

  cout << (Solve(K + 1) + kP - Solve(K)) % kP << "\n";
}

