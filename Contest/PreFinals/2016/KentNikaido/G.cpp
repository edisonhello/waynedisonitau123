#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int h, w, n;
  cin >> h >> w >> n;
  vector<int> row(h, -1);
  vector<int> col(w, -1);
  for (int i = 0; i < n; ++i) {
    int r, c, d;
    cin >> r >> c >> d;
    r--, c--;
    int y = (d >= 3) ^ (r & 1);
    int x = (d == 2 || d == 3) ^ (c & 1);
    if (row[r] != -1 && row[r] != x) {
      cout << "0\n";
      return 0;
    }
    row[r] = x;
    if (col[c] != -1 && col[c] != y) {
      cout << "0\n";
      return 0;
    }
    col[c] = y;
  }

  constexpr int kMod = 1'000'000'000 + 7;

  auto Solve = [&](vector<int> a) {
    int n = a.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(4, vector<int>(2)));
    if (a[0] == -1) dp[0][0][0] = dp[0][0][1] = 1;
    else dp[0][0][a[0]] = 1;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 2; ++k) {
          for (int p = 0; p < 2; ++p) {
            if (a[i] == -1 || a[i] == p) {
              int nj = j;
              if (p == k) nj |= (1 << (p ^ (i & 1)));
              (dp[i][nj][p] += dp[i - 1][j][k]) >= kMod ? dp[i][nj][p] -= kMod : 0;
            }
          }
        }
      }
    }
    vector<int> res(4);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 2; ++j) {
        (res[i] += dp[n - 1][i][j]) >= kMod ? res[i] -= kMod : 0;
      }
    }
    return res;
  };

  auto u = Solve(row), v = Solve(col);
  int res = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (i & j) continue;
      res += 1LL * u[i] * v[j] % kMod;
      res >= kMod ? res -= kMod : 0;
    }
  }
  cout << res << "\n";
  return 0;
}
