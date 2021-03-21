#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<string> grid(N);
  for (int i = 0; i < N; ++i) cin >> grid[i];
  vector<vector<int>> w(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cin >> w[i][j];
  }

  constexpr int kInf = 1'000'000'000;
  vector<int> dp(1 << (N + N), kInf);
  pair<int, int> B[20], W[20];
  int L = -1;
  for (int s = 0; s < (1 << (N + N)); ++s) {
    if (__builtin_popcount(s) != N) continue;
    if (L == -1) {
      L = s;
      dp[s] = 0;
      continue;
    }
    L = s;
    int x = 0, y = 0, p = -1, pb = 0, pw = 0;
    for (int i = 0; i < N + N; ++i) {
      if (s >> i & 1) {
        y++;
        if (p == 0) {
          int t = s ^ (1 << i) ^ (1 << (i - 1));
          int z = w[y - 1][x - 1];
          dp[s] = min(dp[s], dp[t] + z);
          if (grid[y - 1][x - 1] == 'B') {
            for (int j = 0; j < pw; ++j) {
              int r = W[j].first, v = W[j].second;
              dp[s] = min(dp[s], dp[r ^ (1 << i) ^ (1 << (i - 1))] + abs(z - v));
            }
            B[pb++] = make_pair(t, z);
          } else {
            for (int j = 0; j < pb; ++j) {
              int r = B[j].first, v = B[j].second;
              dp[s] = min(dp[s], dp[r ^ (1 << i) ^ (1 << (i - 1))] + abs(z - v));
            }
            W[pw++] = make_pair(t, z);
          }
        }
        p = 1;
      } else {
        x++;
        p = 0;
      }
    }
  }

  cout << dp[L] << "\n";
  return 0;
}
