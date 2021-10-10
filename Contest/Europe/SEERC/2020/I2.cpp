#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int dp[1000006];
int went[1000006];

int main() {
  int n; cin >> n;

  if (n == 1) {
    cout << 1 << endl;
    exit(0);
  }

  dp[1] = 1;

  for (int i = 1; i <= n; ++i) {
    (dp[i + 1] += dp[i]) %= mod;
    went[i] = i;
    went[i + 1] = i;
    
    for (int ii = 2 * i; ii <= n; ii += i) {
      if (went[ii - 1] != i) (dp[ii - 1] += dp[i]) %= mod;
      if (went[ii + 1 - 1] != i) (dp[ii + 1 - 1] += dp[i]) %= mod;
      if (went[ii + 2 - 1] != i) (dp[ii + 2 - 1] += dp[i]) %= mod;

      went[ii - 1] = went[ii + 1 - 1] = went[ii + 2 - 1] = i;
    }
  }

  int ans = 0;
  for (int i = 1; i < n; ++i) {
    // cerr << "dp " << i << ' ' << dp[i] << endl;
    (ans += dp[i]) %= mod;
  }

  cout << (ans * 1ll * n % mod) << endl;
}
