#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
using namespace std;

namespace fft {

constexpr int kN = 262144;
constexpr int kP = 998244353;
constexpr int kR = 3;
int omega[kN + 1];

int fpow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) res = 1LL * res * a % kP;
    a = 1LL * a * a % kP;
    n >>= 1;
  }
  return res;
}

void Init() {
  int x = fpow(kR, (kP - 1) / kN);
  omega[0] = 1;
  for (int i = 1; i <= kN; ++i) {
    omega[i] = 1LL * omega[i - 1] * x % kP;
  }
}

void BitReverse(vector<int> &v, int n) {
  int z = __builtin_ctz(n) - 1;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    for (int j = 0; (1 << j) < n; ++j) {
      x ^= (i >> j & 1) << (z - j);
    }
    if (x > i) swap(v[x], v[i]);
  }
}

void Transform(vector<int> &v, int n) {
  BitReverse(v, n);
  for (int s = 2; s <= n; s <<= 1) {
    int z = s >> 1;
    for (int i = 0; i < n; i += s) {
      for (int k = 0; k < z; ++k) {
        int x = 1LL * v[i + k + z] * omega[kN / s * k] % kP;
        v[i + k + z] = (v[i + k] + kP - x) % kP;
        (v[i + k] += x) %= kP;
      }
    }
  }
}

void InvTransform(vector<int> &v, int n) {
  Transform(v, n);
  for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
  const int kI = fpow(n, kP - 2);
  for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * kI % kP;
}

vector<int> Multiply(vector<int> a, vector<int> b) {
  int n = a.size(), m = b.size(), k = 1;
  while (k < n + m - 1) k <<= 1;
  a.resize(k);
  b.resize(k);
  Transform(a, k);
  Transform(b, k);
  for (int i = 0; i < k; ++i) a[i] = 1LL * a[i] * b[i] % kP;
  InvTransform(a, k);
  a.resize(n + m - 1);
  return a;
}

}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  using namespace fft;
  Init();
  int T;
  cin >> T;
  vector<int> fc(kN, 1), iv(kN, 1);
  for (int i = 1; i < kN; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  auto Binom = [&](int n, int k) {
    return 1LL * fc[n] * iv[k] % kP * iv[n - k] % kP;
  };

  auto InvBinom = [&](int n, int k) {
    return 1LL * iv[n] * fc[k] % kP * fc[n - k] % kP;
  };

  while (T--) {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    auto Solve = [&](auto dfs, int l, int r) -> vector<int> {
      if (r - l == 1) return {kP - A[l] % kP, 1};
      int m = (l + r) >> 1;
      return fft::Multiply(dfs(dfs, l, m), dfs(dfs, m, r));
    };

    vector<int> poly = Solve(Solve, 0, N);
    int ans = 0;
    for (int i = 0; i < N; ++i) {
      int cf = poly[i];
      if (i % 2 != N % 2) cf = kP - cf;
      ans += 1LL * InvBinom(N, i) * cf % kP;
      ans %= kP;
    }
    cout << ans << "\n";
  }
}
