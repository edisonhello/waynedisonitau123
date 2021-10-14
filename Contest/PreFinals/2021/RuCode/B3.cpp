#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int N = s.size();
  vector<vector<int>> nxt(N, vector<int>(10, N));
  vector<int> last(10, N);
  for (int i = N - 1; i >= 0; --i) {
    last[s[i] - '0'] = i;
    for (int j = 0; j < 10; ++j) nxt[i][j] = last[j];
  }
  vector<int> dp(1024, N + 1);
  vector<int> ndp(1024, N + 1);
  dp[0] = -1;
  int ans = N;
  for (int t = 0; t <= N; ++t) {
    fill(ndp.begin(), ndp.end(), N + 1);
    cout << "t = " << t << endl;
    for (int mask = 0; mask < 1024; ++mask) {
      if (dp[mask] == N + 1) continue; 
      if (dp[mask] == N - 1) {
        ans = min(ans, N - t);
        continue;
      }
      cout << "dp[" << mask << "] = " << dp[mask] << endl;
      if (dp[mask] == -1) {
        for (int i = 0; i < 10; ++i) {
          if (nxt[0][i] != N) {
            ndp[(1 << i)] = min(ndp[(1 << i)], nxt[0][i]);
          }
        }
        continue;
      }
      int p = dp[mask] + 1;
      assert(p > 0);
      if (nxt[p][s[p - 1] - '0'] != N) {
        ndp[mask] = min(ndp[mask], nxt[p][s[p - 1] - '0']);
      } else {
        ans = min(ans, N - t);
      }
      if ((mask >> (s[p] - '0') & 1) == 0) {
        ndp[mask ^ (1 << (s[p] - '0'))] =
            min(ndp[mask ^ (1 << (s[p] - '0'))], p);
      }
    }
    dp.swap(ndp);
  }
  cout << ans << "\n";
}
