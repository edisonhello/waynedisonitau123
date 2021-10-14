#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, D;
  cin >> N >> D;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  vector<vector<double>> dp(N + 1, vector<double>(10, -1E9));
  vector<vector<int>> fr(N + 1, vector<int>(10, -1));
  dp[0][1] = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (dp[i][j] > dp[i + 1][j]) {
        dp[i + 1][j] = dp[i][j];
        fr[i + 1][j] = j;
      }
      if (dp[i][j] + log(A[i]) > dp[i + 1][(j * A[i]) % 10]) {
        dp[i + 1][(j * A[i]) % 10] = dp[i][j] + log(A[i]);
        fr[i + 1][(j * A[i]) % 10] = j;
      }
    }
  }
  constexpr double kEps = 1E-6;
  if (dp[N][D] < -10) {
    cout << "-1\n";
    return 0;
  }
  if (fabs(dp[N][D]) < kEps) {
    assert(D == 1);
    if (count(A.begin(), A.end(), 1) == 0) {
      cout << "-1\n";
    } else {
      cout << "1\n1\n";
    }
    return 0;
  }
  vector<int> ans;
  for (int i = N, j = D; i > 0; --i) {
    if (dp[i][j] > dp[i - 1][fr[i][j]] + kEps) {
      ans.push_back(i - 1);
    }
    j = fr[i][j];
  }
  cout << ans.size() << "\n";
  for (int u : ans) cout << A[u] << " ";
  cout << "\n";
}
