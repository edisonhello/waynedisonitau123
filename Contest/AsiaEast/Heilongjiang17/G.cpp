#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int dp[2005][2005];
int can[2005][2005];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  dp[0][0] = 1;
  can[0][0] = 1;

  for (int i = 1; i <= n; ++i) {
    int item = v[i - 1];
    for (int j = n; j >= 0; --j) {
      if (j >= item and item != 0) {
        dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - item]) % mod;
        can[i][j] = can[i - 1][j] | can[i - 1][j - item];
      } else {
        dp[i][j] = dp[i - 1][j];
        can[i][j] = can[i - 1][j];
      }
    }

    // for (int j = 0; j <= n; ++j) {
    //   cerr << dp[i][j] << ' ';
    // }
    // cerr << endl;
  }

  for (int i = n; i >= 0; --i) {
    if (can[n][i]) {
      cout << i << ' ';
      cout << dp[n][i] << endl;
      return 0;
    }
  }

}

