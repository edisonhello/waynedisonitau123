#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  vector<vector<int>> A(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> A[i][j];
    }
  }
  constexpr int kP = 998244353;

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kP;
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  vector<int> e(N);
  e[0] = 1;

  auto Next = [&](const vector<int> &e) {
    vector<int> res(N);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        res[i] += 1LL * A[i][j] * e[j] % kP;
        res[i] %= kP;
      }
    }
    return res;
  };

  vector<vector<int>> basis(N);
  vector<vector<int>> g(N, vector<int>(N));
  basis[0] = e;
  g[0][0] = 1;
  vector<vector<int>> H(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    auto v = Next(e);
    auto w = v;
    vector<int> cf(N);
    for (int j = 0; j < N; ++j) {
      if (!basis[j].empty() && v[j]) {
        int coef = 1LL * v[j] * fpow(basis[j][j], kP - 2) % kP;
        for (int k = 0; k < N; ++k) {
          cf[k] += 1LL * coef * g[j][k] % kP;
          cf[k] %= kP;
        }
        for (int k = 0; k < N; ++k) {
          v[k] += kP - 1LL * coef * basis[j][k] % kP;
          v[k] %= kP;
        }
      }
    }
    int t = *max_element(v.begin(), v.end());
    vector<int> nxt;
    if (t > 0) {
      for (int j = 0; j < N; ++j) {
        if (basis[j].empty() && v[j]) {
          basis[j] = v;
          for (int k = 0; k < N; ++k) g[j][k] = (kP - cf[k]) % kP;
          g[j][j] = 1;
          break;
        }
      }
      if (i + 1 < N) {
        H[i + 1][i] = 1;
      } else {
        for (int j = 0; j < N; ++j) {
          H[j][i] = cf[j];
        }
      }
      nxt = w;
    } else {
      for (int j = 0; j < N; ++j) {
        if (basis[j].empty()) {
          basis[j].resize(N);
          basis[j][j] = 1;
          g[j][j] = 1;
          nxt = basis[j];
          break;
        }
      }
      for (int j = 0; j < N; ++j) {
        H[j][i] = cf[j];
      }
    }
    e = nxt;
  }

  auto Mult = [&](const vector<int> &a, const vector<int> &b) {
    vector<int> res(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
      for (int j = 0; j < b.size(); ++j) {
        res[i + j] += 1LL * a[i] * b[j] % kP;
        res[i + j] %= kP;
      }
    }
    return res;
  };

  vector<int> beta(N + 1);
  for (int i = 0; i + 1 < N; ++i) {
    beta[i + 1] = kP - H[i + 1][i];
  }

  vector<vector<int>> p(N + 1);
  p[0] = {1};
  for (int i = 1; i <= N; ++i) {
    auto q = Mult(p[i - 1], {H[i - 1][i - 1], kP - 1});
    for (int m = 1; m <= i - 1; ++m) {
      int h = H[i - m - 1][i - 1];
      for (int j = i - m + 1; j <= i; ++j) {
        h = 1LL * h * beta[j - 1] % kP;
      }
      if (q.size() < p[i - m - 1].size()) {
        q.resize(p[i - m - 1].size());
      }
      for (int k = 0; k < p[i - m - 1].size(); ++k) {
        q[k] += 1LL * h * p[i - m - 1][k] % kP;
        q[k] %= kP;
      }
    }
    p[i] = q;
  }
  while (Q--) {
    int x;
    cin >> x;
    int res = 0;
    int pd = 1;
    for (int i = 0; i < p[N].size(); ++i) {
      res += 1LL * pd * p[N][i] % kP;
      res %= kP;
      pd = 1LL * pd * x % kP;
    }
    cout << res << " ";
  }
  return 0;
}
