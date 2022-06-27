#include <bits/stdc++.h>
using namespace std;

int s[3000];
int dp[3000];
int pre[3000];

int C[3000][3000];

int main() {
  int r, n, m; cin >> r >> n >> m;

  C[0][0] = 1;
  for (int i = 1; i < 3000; ++i) {
    for (int j = 0; j <= i; ++j) {
      C[i][j] = C[i - 1][j];
      if (j) {
        C[i][j] += C[i - 1][j - 1];
        if (C[i][j] >= m) C[i][j] -= m;
      }
    }
  }

  s[0] = s[1] = s[2] = 1 % m;

  for (int i = 3; i <= n; ++i) {
    int sum = 0;
    if (i % 2 == 1) {
      for (int j = 0 ;j <= i / 2 - 1; ++j) {
        sum += 1ll * s[j] * s[i - j - 1] % m * C[i - 1][j] % m; 

        if (sum >= m) sum -= m;
      }

      sum += 1ll * s[i / 2] * s[i - i / 2 - 1] % m * C[i - 2][i / 2 - 1] % m; 
      if (sum >= m) sum -= m;
    } else {
      for (int j = 0 ;j <= i / 2 - 1; ++j) {
        sum += 1ll * s[j] * s[i - j - 1] % m * C[i - 1][j] % m; 

        if (sum >= m) sum -= m;
      }
    }

    s[i] = sum;
  }

  // for (int i = 0; i <= 20; ++i) cout << s[i] << ' ';
  // cout << endl;

  int j = n - r + 1;
  dp[j] = s[j];
  for (int i = j + 1; i <= n; ++i) {
    int sum = s[i];
    for (int v = 1; v <= i; ++v) {
      sum -= 1ll * dp[i - v] * s[v + 1] % m * C[i - j][v] % m;
      if (sum < 0) sum += m;
    }
    dp[i] = sum;
  }

  cout << dp[n] % m << endl;


}

