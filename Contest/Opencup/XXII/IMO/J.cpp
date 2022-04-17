#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> p(N);
  vector<int> order(N);
  for (int i = 0; i < N; ++i) {
    cin >> p[i];
    p[i]--;
  }
  vector<int> q(N);
  for (int i = 0; i < N; ++i) {
    cin >> q[p[i]];
    q[p[i]]--;
  }
  vector<int> vec;
  vector<bool> used(N);
  for (int i = 0; i < N; ++i) {
    if (q[i] >= 0) {
      vec.push_back(i);
      used[q[i]] = true;
    }
  }
  vector<int> cnt(N + 1);
  for (int i = 0; i < N; ++i) {
    if (!used[i]) {
      cnt[i + 1]++;
    }
  }
  for (int i = 1; i <= N; ++i) {
    cnt[i] += cnt[i - 1];
  }

  constexpr int kP = 998244353;
  vector<int> fact(N + 1, 1);
  for (int i = 1; i <= N; ++i) {
    fact[i] = 1LL * fact[i - 1] * i % kP;
  }
  vector<vector<int>> bin(N + 1, vector<int>(N + 1));
  for (int i = 0; i <= N; ++i) {
    bin[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      bin[i][j] = (bin[i - 1][j] + bin[i - 1][j - 1]) % kP;
    }
  }
  int M = cnt[N];
  vector<vector<int>> dp(vec.size(), vector<int>(M + 1));
  for (int i = 0; i < vec.size(); ++i) {
    for (int k = 0; k <= M; ++k) {
      int c = cnt[q[vec[i]]];
      dp[i][k] = 1LL * bin[c][k] * bin[vec[i] - i][k] % kP;
    }
    for (int j = 0; j < i; ++j) {
      if (q[vec[i]] > q[vec[j]]) {
        int c = cnt[q[vec[i]]] - cnt[q[vec[j]]];
        for (int k = 0; k <= M; ++k) {
          for (int t = 0; t <= k; ++t) {
            dp[i][k] += 1LL * bin[c][k - t] *
                        bin[vec[i] - vec[j] - 1 - (i - j - 1)][k - t] % kP *
                        dp[j][t] % kP;
            dp[i][k] %= kP;
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < vec.size(); ++i) {
    for (int k = 0; k <= M; ++k) {
      if (dp[i][k] > 0) {
        int c = cnt[N] - cnt[q[vec[i]]];
        for (int t = 0; t + k <= M; ++t) {
          int ways = 1LL * dp[i][k] * bin[c][t] % kP *
                     bin[N - vec[i] - 1 - (vec.size() - i - 1)][t] % kP;
          ans += 1LL * ways * fact[M - (t + k)] % kP;
          ans %= kP;
        }
      }
    }
  }
  for (int i = 0; i <= M; ++i) {
    ans += 1LL * bin[M][i] * bin[M][i] % kP * fact[M - i] % kP;
    ans %= kP;
  }
  cout << ans << "\n";
  return 0;
}
