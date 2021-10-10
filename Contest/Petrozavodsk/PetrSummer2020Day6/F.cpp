#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int a[2005], c[2005];
long long dp[2005][2005], prv[2005][2005];

int main() {
  int n, K, P; cin >> n >> K >> P;
  // for (int i = 1; i <= n; ++i) cin >> a[i];
  // for (int i = 1; i <= n; ++i) cin >> c[i];
  for (int i = 1; i <= n; ++i) a[i] = rand() % 100000;
  for (int i = 1; i <= n; ++i) c[i] = rand() % 100000;

  memset(prv, 0xc0, sizeof(prv));
  memset(dp, 0xc0, sizeof(dp));

  prv[0][0] = 0;

  for (int i = 1; i <= n; ++i) {
    // cerr << "at i = " << i << endl;
  
    int mxj = min(i - 1, K);
    for (int j = 0; j <= mxj; ++j) {

      int A = a[i];
      long long mx = 0;
      for (int k = 0; k <= j; ++k) {
        // cerr << "j k " << j << ' ' << k << ' ' << prv[j][k] << endl;

        // press
        dp[j + 1][k + 1] = prv[j][k] + 1ll * A * c[k + 1];
        // dp[j + 1][k + 1] = max(dp[j + 1][k + 1], prv[j][k] + a[i] * c[k + 1]);

        // no press
        mx = max(mx, prv[j][k] + (k ? P : 0));
      }

      dp[j][0] = mx;
    }

    swap(dp, prv);
    memset(dp, 0xc0, sizeof(dp));

    // for (int j = 0; j <= mxj; ++j) {
    //   for (int k = 0; k <= j; ++k) {
    //     cerr << prv[j][k] << ' ';
    //   }
    //   cerr << endl;
    // }
  }

  long long mx = 0;
  for (int j = 0; j <= K; ++j) {
    for (int k = 0; k <= K; ++k) {
      mx = max(mx, prv[j][k] + (k ? P : 0));
    }
  }

  cout << mx << endl;
}
