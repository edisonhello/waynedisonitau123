#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  string a, b;
  cin >> a >> b;
  string s = "";
  for (int i = 0; i < N; ++i) {
    if (a[i] == b[i]) {
      s += 'x';
    } else {
      s += a[i];
    }
  }

  constexpr int kP = 1'000'000'000 + 7;
  vector<pair<int, int>> vec;
  vector<int> gap;
  for (int i = 0, j = 0, g = 0; i < N; i = j) {
    if (s[i] == 'x') {
      g++;
      j = i + 1;
    } else {
      while (j + 1 < N && s[j + 1] != 'x' && s[j + 1] != s[j]) {
        j++;
      }
      vec.emplace_back(i, j);
      gap.push_back(g);
      j++;
      g = 0;
    }
  }

  int M = vec.size();
  vector<vector<int>> dp(M + 1, vector<int>(2));
  dp[0][0] = 1;
  for (int i = 0; i < vec.size(); ++i) {
    int len = vec[i].second - vec[i].first + 1;
    if (len % 2 == 0) {
      // take all
      dp[i + 1][0] = dp[i][0];
    } else {
      if (len == 1) {
        // take now, not match
        dp[i + 1][0] = dp[i][0] % kP;
        // take now, match
        if (i > 0 && gap[i] == 1 && s[vec[i - 1].second] != s[vec[i].first]) {
          dp[i + 1][0] += dp[i][1] * 2 % kP;
          dp[i + 1][0] %= kP;
        }
        // don't take
        dp[i + 1][1] = dp[i][0] % kP;
      } else {
        // left first
        {
          // not match
          dp[i + 1][0] = dp[i][0] % kP;
          // match
          if (i > 0 && gap[i] == 1 && s[vec[i - 1].second] != s[vec[i].first]) {
            dp[i + 1][0] += dp[i][1] * 2 % kP;
            dp[i + 1][0] %= kP;
          }
        }
        // left last
        dp[i + 1][1] = dp[i][0] % kP;

        // left mid
        dp[i + 1][0] += 1LL * (len - 3) / 2 * dp[i][0] % kP;
        dp[i + 1][0] %= kP;

        // don't left
        (dp[i + 1][0] += dp[i][0]) %= kP;
      }
    }
    // cerr << "dp[0] = " << dp[i + 1][0] << " dp[1] = " << dp[i + 1][1] << endl;
  }
  cout << dp.back()[0] % kP << "\n";
  return 0;
}
