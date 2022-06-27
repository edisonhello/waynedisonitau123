#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kP = 998244353;
constexpr int kR = 3;

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
};

namespace fft {

constexpr int kN = 262144;
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
  const int kInv = fpow(n, kP - 2);
  for (int i = 0; i < n; ++i) {
    v[i] = 1LL * v[i] * kInv % kP;
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

vector<int> Inverse(vector<int> f) {
  int n = f.size();
  vector<int> q(1, fpow(f[0], kP - 2));
  for (int s = 2;; s <<= 1) {
    if (f.size() < s) {
      f.resize(s);
    }
    vector<int> fv(f.begin(), f.begin() + s);
    vector<int> fq(q.begin(), q.end());
    fv.resize(s + s);
    fq.resize(s + s);
    Transform(fv, s + s);
    Transform(fq, s + s);
    for (int i = 0; i < s + s; ++i) {
      fv[i] = 1LL * fv[i] * fq[i] % kP * fq[i] % kP;
    }
    InvTransform(fv, s + s);
    vector<int> res(s);
    for (int i = 0; i < s; ++i) {
      res[i] = kP - fv[i];
      if (i < (s >> 1)) {
        int v = 2 * q[i] % kP;
        (res[i] += v) %= kP;
      }
    }
    q = res;
    if (s >= n) {
      break;
    }
  }
  q.resize(n);
  return q;
}

vector<int> Integral(const vector<int>& f) {
  int n = f.size();
  vector<int> res(n + 1);
  for (int i = 0; i < n; ++i) {
    res[i + 1] = 1LL * f[i] * fpow(i + 1, kP - 2) % kP;
  }
  return res;
}

vector<int> Derivative(const vector<int>& f) {
  int n = f.size();
  vector<int> res(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    res[i] = 1LL * f[i + 1] * (i + 1) % kP;
  }
  return res;
}

vector<int> Log(vector<int> f) {
  int n = f.size();
  if (n == 1) {
    return {0};
  }
  vector<int> d = Derivative(f);
  f.resize(n - 1);
  d = Multiply(d, Inverse(f));
  d.resize(n - 1);
  return Integral(d);
}

vector<int> Exp(vector<int> f) {
  int n = f.size();
  f[0] += 1;
  vector<int> q(1, 1);
  for (int s = 1; s < n; s <<= 1) {
    if (f.size() < s + s) {
      f.resize(s + s);
    }
    vector<int> g(f.begin(), f.begin() + s + s);
    vector<int> h(q.begin(), q.end());
    h.resize(s + s);
    h = Log(h);
    for (int i = 0; i < s + s; ++i) {
      g[i] = (g[i] + kP - h[i]) % kP;
    }
    g = Multiply(g, q);
    g.resize(s + s);
    q = g;
  }
  assert(q.size() >= n);
  q.resize(n);
  return q;
}

}  // namespace fft

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  fft::Init();
  int N, M;
  cin >> N >> M;

  vector<int> fc(N + 1, 1), iv(N + 1, 1);
  for (int i = 1; i <= N; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  auto Bin = [&](int n, int k) -> int64_t {
    return 1LL * fc[n] * iv[k] % kP * iv[n - k] % kP;
  };

  vector<int> g(N + 1);
  for (int i = 1; i <= N; ++i) {
    int t = i / __gcd(i, M);
    g[t] = __gcd(g[t], i / t);
  }

  vector<int> dp(N + 1);
  vector<int> new_dp(N + 1);
  dp[0] = 1;
  vector<int> sum(N + 1);
  for (int i = 1; i <= N; ++i) {
    if (g[i] > 0) {
      vector<int> poly(N / i + 1);
      for (int j = 0; j <= N / i; j += g[i]) {
        poly[j] = 1LL * fpow(fpow(i, j), kP - 2) * iv[j] % kP;
      }
      poly = fft::Log(poly);
      for (int j = 0; j <= N / i; ++j) {
        (sum[j * i] += poly[j]) %= kP;
      }
    }
  }
  sum = fft::Exp(sum);
  cout << 1LL * fc[N] * sum[N] % kP << "\n";
  return 0;
}
