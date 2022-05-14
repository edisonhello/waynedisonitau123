#include <bits/stdc++.h>
using namespace std;

constexpr int kP = 998244353;

int fpow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) {
      res = 1LL * res * a % kP;
    }
    a = 1LL * a * a % kP;
    n >>= 1;
  }
  return res;
}

namespace fft {

constexpr int kR = 3;
constexpr int kN = 524288;

int omega[kN + 1];

void Init() {
  int x = fpow(kR, (kP - 1) / kN);
  omega[0] = 1;
  for (int i = 1; i <= kN; ++i) {
    omega[i] = 1LL * omega[i - 1] * x % kP;
  }
}

void BitReverse(vector<int>& v, int n) {
  int z = __builtin_ctz(n) - 1;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    for (int j = 0; (1 << j) < n; ++j) {
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
        int x = 1LL * v[i + z + k] * omega[kN / s * k] % kP;
        v[i + z + k] = (v[i + k] + kP - x) % kP;
        v[i + k] = (v[i + k] + x) % kP;
      }
    }
  }
}

void InvTransform(vector<int>& v, int n) {
  Transform(v, n);
  reverse(v.begin() + 1, v.end());
  const int kI = fpow(n, kP - 2);
  for (int i = 0; i < n; ++i) {
    v[i] = 1LL * v[i] * kI % kP;
  }
}

vector<int> Multiply(vector<int> a, vector<int> b) {
  int n = a.size(), m = b.size(), sz = 1;
  while (sz < n + m - 1) {
    sz <<= 1;
  }
  a.resize(sz);
  b.resize(sz);
  Transform(a, sz);
  Transform(b, sz);
  for (int i = 0; i < sz; ++i) {
    a[i] = 1LL * a[i] * b[i] % kP;
  }
  InvTransform(a, sz);
  a.resize(n + m - 1);
  return a;
}

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  fft::Init();
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N, L, m;
    cin >> N >> L >> m;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
      cin >> A[N - i - 1];
    }
    vector<int> p1(N);
    int coeff = 1;
    for (int i = 0; i < N; ++i) {
      p1[i] = coeff;
      coeff = 1LL * coeff * (m + i) % kP;
      coeff = 1LL * coeff * fpow(i + 1, kP - 2) % kP;
    }
    vector<int> p2(N);
    coeff = 1;
    for (int i = 0; 1LL * i * L < N; ++i) {
      p2[i * L] = coeff;
      if (i & 1) {
        p2[i * L] = (kP - p2[i * L]) % kP;
      }
      coeff = 1LL * coeff * fpow(i + 1, kP - 2) % kP;
      coeff = 1LL * coeff * (m - i) % kP;
    }
    // cerr << "p1 = ";
    // for (int i = 0; i < N; ++i) cerr << p1[i] << " "; cerr << endl;
    // cerr << "p2 = ";
    // for (int i = 0; i < N; ++i) cerr << p2[i] << " "; cerr << endl;
    vector<int> ans = fft::Multiply(p1, p2);
    ans.resize(N);
    ans = fft::Multiply(ans, A);
    cout << "Case " << tc << ":";
    for (int i = 0; i < N; ++i) {
      cout << " " << ans[N - i - 1];
    }
    cout << "\n";
  }
  return 0;
}
