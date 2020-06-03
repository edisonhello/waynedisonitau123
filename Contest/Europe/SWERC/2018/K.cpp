#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  vector<vector<int>> rep(n, vector<int>(n, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      bool ok = true;
      int z = j - i + 1;
      for (int k = i; k < n; k += z) {
        if (k + z > n) break;
        for (int g = 0; g < z; ++g) ok &= s[k + g] == s[i + g];
        if (!ok) break;
        if (rep[i][k + z - 1] == -1 || rep[i][k + z - 1] > z) {
          rep[i][k + z - 1] = z;
        }
      }
    }
  }
  vector<vector<int>> dp(n, vector<int>(n, n));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j + i <= n; ++j) {
      int l = j, r = i + j - 1;
      assert(rep[l][r] != -1);
      dp[l][r] = r - l + 1;
      if (rep[l][r] < (r - l + 1)) {
        dp[l][r] = dp[l][l + rep[l][r] - 1];
      }
      for (int k = l; k < r; ++k) {
        dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
      }
    }
  }
  cout << dp[0][n - 1] << "\n";
}
