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
constexpr int kN = 1048576;
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
        int x = 1LL * v[i + k + z] * omega[kN / s * k] % kP;
        v[i + k + z] = (v[i + k] + kP - x) % kP;
        v[i + k] = (v[i + k] + x) % kP;
      }
    }
  }
}

void InvTransform(vector<int>& v, int n) {
  Transform(v, n);
  for (int i = 1; i < n / 2; ++i) {
    swap(v[i], v[n - i]);
  }
  const int kI = fpow(n, kP - 2);
  for (int i = 0; i < n; ++i) {
    v[i] = 1LL * v[i] * kI % kP;
  }
}

vector<int> Multiply(vector<int> a, vector<int> b) {
  int n = a.size(), m = b.size(), s = 1;
  while (s < n + m - 1) {
    s <<= 1;
  }
  a.resize(s);
  b.resize(s);
  Transform(a, s);
  Transform(b, s);
  for (int i = 0; i < s; ++i) {
    a[i] = 1LL * a[i] * b[i] % kP;
  }
  InvTransform(a, s);
  a.resize(n + m - 1);
  return a;
}

}  // namespace fft

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  fft::Init();
  int N;
  cin >> N;
  string s;
  cin >> s;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }

  vector<int> fc(N + 1, 1), iv(N + 1, 1);
  for (int i = 1; i <= N; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  auto Solve = [&](const string& s, char ch) {
    vector<int> p(N), q(N);
    vector<int> sum(N);
    for (int i = 0; i < N; ++i) {
      if (s[i] != ch) {
        sum[i] = A[i];
      }
      if (i > 0) {
        sum[i] += sum[i - 1];
        sum[i] %= kP;
      }
    }
    for (int i = 0; i < N; ++i) {
      if (s[i] == ch) {
        p[i] = sum[i];
        q[N - 1 - i] = 1;
      }
    }
    vector<int> res(N);
    vector<int> a = fft::Multiply(p, q);
    for (int i = 0; i < N; ++i) {
      res[i] = a[N - 1 + i];
    }
    for (int i = 0; i < N; ++i) {
      if (s[i] == ch) {
        p[i] = 1;
        q[N - 1 - i] = kP - sum[i];
      }
    }
    a = fft::Multiply(p, q);
    for (int i = 0; i < N; ++i) {
      (res[i] += a[N - 1 + i]) %= kP;
    }
    int ans = 0;
    for (int i = 1; i < N; ++i) {
      if (res[i] > 0) {
        int ways = 2LL * fc[i - 2] * iv[i + 1] % kP;
        ans += 1LL * res[i] * ways % kP;
        ans %= kP;
      }
    }
    return ans;
  };

  int ans = (Solve(s, 'W') + Solve(s, 'B')) % kP;
  cout << 1LL * fc[N] * ans % kP << "\n";
}
