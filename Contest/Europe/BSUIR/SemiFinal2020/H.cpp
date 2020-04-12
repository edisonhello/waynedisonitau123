#include <bits/stdc++.h>
using namespace std;

constexpr int K = 4000;
array<int, K * K> dp;

int main() {
  fill(dp.begin(), dp.end(), 1e9);
  dp[0] = 0;
  for (int i = 1; i < K * K; ++i) {
    for (int j = 1; j <= K && i >= j * (j - 1); ++j) {
      dp[i] = min(dp[i - j * (j - 1)] + j, dp[i]);
    }
  }
  string s = "";
  for (int i = 2; i < K * K; i += 2) {
    int diff = dp[i] - dp[i - 2];
    s += (char)(diff);
  }
  cout << s << "\n";
}
