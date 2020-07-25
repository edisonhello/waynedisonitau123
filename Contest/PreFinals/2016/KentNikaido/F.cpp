#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr double kEps = 1E-9;

bool Simplex(vector<vector<double>> A, vector<double> b, vector<double> c) {
  int m = b.size(), n = c.size();
  vector<vector<double>> D(m + 2, vector<double>(n + 2));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      D[i][j] = A[i][j];
    }
  }
  vector<int> p(m), q(n + 1);
  for (int i = 0; i < m; ++i) {
    p[i] = n + i;
    D[i][n] = -1;
    D[i][n + 1] = b[i];
  }
  for (int i = 0; i < n; ++i) {
    q[i] = i;
    D[m][i] = -c[i];
  }
  q[n] = -1;
  D[m + 1][n] = 1;
  int r = 0;
  for (int i = 1; i < m; ++i) {
    if (D[i][n + 1] < D[r][n + 1]) r = i;
  }

  auto Pivot = [&](int r, int s) {
    double inv = 1.0 / D[r][s];
    for (int i = 0; i < m + 2; ++i) {
      for (int j = 0; j < n + 2; ++j) {
        if (i != r && j != s) {
          D[i][j] -= D[r][j] * D[i][s] * inv;
        }
      }
    }
    for (int i = 0; i < m + 2; ++i) {
      if (i != r) D[i][s] /= -D[r][s];
    }
    for (int j = 0; j < n + 2; ++j) {
      if (j != s) D[r][j] /= D[r][s];
    }
    D[r][s] = 1.0 / D[r][s];
    swap(p[r], q[s]);
  };

  auto Phase = [&](int z) {
    int x = m + z;
    while (clock() <= 0.94 * CLOCKS_PER_SEC) {
      int s = -1;
      for (int i = 0; i <= n; ++i) {
        if (!z && q[i] == -1) continue;
        if (s == -1 || D[x][i] < D[x][s]) s = i;
      }
      if (D[x][s] > -kEps) return true;
      int r = -1;
      for (int i = 0; i < m; ++i) {
        if (D[i][s] < kEps) continue;
        if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s]) r = i;
      }
      if (r == -1) return false;
      Pivot(r, s);
    }
    cout << "NO" << '\n';
    exit(0);
  };

  if (D[r][n + 1] < kEps) {
    Pivot(r, n);
    if (!Phase(1) || D[m + 1][n + 1] < -kEps) {
      return false;
    }
  }
  return true;
}

int main() {
  int n;
  cin >> n;
  vector<string> s(n);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }
  vector<vector<double>> A;
  vector<double> b;
  vector<vector<vector<int>>> rect(n - 1, vector<vector<int>>(n - 1));
  int cnt = 2 * (n - 1) * n;
  int e = 0;

  auto MustBe = [&](int x, int y) {
    vector<double> w(cnt);
    w[x] = 1;
    A.push_back(w);
    b.push_back(y);
    w[x] = -1;
    A.push_back(w);
    b.push_back(-y);
  };

  auto Maybe = [&](int x) {
    vector<double> w(cnt);
    w[x] = 1;
    A.push_back(w);
    b.push_back(1);
    w[x] = -1;
    A.push_back(w);
    b.push_back(0);
  };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i + 1 < n) {
        if (s[i][j] == s[i + 1][j]) {
          MustBe(e, 1);
        } else {
          if ((s[i][j] == 'o' || s[i][j] == 'x') && (s[i + 1][j] == 'o' || s[i + 1][j] == 'x')) {
            MustBe(e, 0);
          } else {
            Maybe(e);
          }
        }
        if (j < n - 1) rect[i][j].push_back(e);
        if (j > 0) rect[i][j - 1].push_back(e);
        e++;
      }
      if (j + 1 < n) {
        if (s[i][j] == s[i][j + 1]) {
          MustBe(e, 1);
        } else {
          if ((s[i][j] == 'o' || s[i][j] == 'x') && (s[i][j + 1] == 'o' || s[i][j + 1] == 'x')) {
            MustBe(e, 0);
          } else {
            Maybe(e);
          }
        }
        if (i < n - 1) rect[i][j].push_back(e);
        if (i > 0) rect[i - 1][j].push_back(e);
        e++;
      }
    }
  }
  assert(e == cnt);
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - 1; ++j) {
      assert(rect[i][j].size() == 4);
      vector<double> w(cnt);
      for (int k = 0; k < 4; ++k) w[rect[i][j][k]] = 1;
      A.push_back(w);
      b.push_back(2);
      for (int k = 0; k < 4; ++k) w[rect[i][j][k]] = -1;
      A.push_back(w);
      b.push_back(-2);
    }
  }
  if (Simplex(A, b, vector<double>(cnt, 1))) cout << "YES\n";
  else cout << "NO\n";
  return 0;
}
