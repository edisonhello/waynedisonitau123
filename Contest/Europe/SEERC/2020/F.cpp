#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> H(N), pos(N);
  for (int i = 0; i < N; ++i) {
    cin >> H[i];
    H[i]--;
    pos[H[i]] = i;
  }
  constexpr int kP = 1'000'000'000 + 7;
  vector<vector<int>> dp(N, vector<int>(N));
  vector<vector<int>> left(N), right(N);
  for (int i = 0; i < N; ++i) {
    int A = H[i];
    for (int j = i - 1; j >= 0; --j) {
      if (H[j] < A) {
        A = H[j];
        left[i].push_back(A);
      }
    }
    A = H[i];
    for (int j = i + 1; j < N; ++j) {
      if (H[j] < A) {
        A = H[j];
        right[i].push_back(A);
      }
    }
  }
  dp[0][H[0]] = 1;
  for (int i : right[0]) {
    dp[0][i] = 1;
  }
  for (int i = 0; i + 1 < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (dp[i][j] == 0) continue;
      if (j <= H[i + 1]) {
        (dp[i + 1][j] += dp[i][j]) %= kP;
      }
      if (H[i + 1] < j || pos[j] <= i) {
        (dp[i + 1][H[i + 1]] += dp[i][j]) %= kP;
      }
      // int A = H[i + 1];
      // for (int k = i + 2; k < N; ++k) {
      //   if (H[k] < A) {
      //     A = H[k]; 
      //     if (A < j || pos[j] <= i) {
      //       (dp[i + 1][A] += dp[i][j]) %= kP;
      //     }
      //   }
      // }
    }
    vector<int> sum(N);
    vector<int> bad(N);
    for (int j = 0; j < N; ++j) {
      if (pos[j] <= i) {
        sum[j] = dp[i][j];
      } else {
        bad[j] = dp[i][j];
      }
      if (j > 0) {
        (sum[j] += sum[j - 1]) %= kP;
      }
    }
    for (int j = N - 2; j >= 0; --j) {
      (bad[j] += bad[j + 1]) %= kP;
    }
    for (int u : left[i + 1]) {
      if (u > 0) (dp[i + 1][u] += sum[u - 1]) %= kP;
    }
    for (int u : right[i + 1]) {
      (dp[i + 1][u] += sum.back()) %= kP;
      if (u + 1 < N) (dp[i + 1][u] += bad[u + 1]) %= kP;
    }
  }
  // for (int i = 0; i < N; ++i) {
  //   for (int j = 0; j < N; ++j) {
  //     cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
  //   }
  // }
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    (ans += dp[N - 1][i]) %= kP;
  }
  cout << ans << "\n";
}
