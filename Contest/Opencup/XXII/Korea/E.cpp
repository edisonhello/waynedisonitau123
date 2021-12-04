#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K;
  int64_t P;
  cin >> N >> K >> P;

  vector<int64_t> c(N), w(N);
  for (int i = 0; i < N; ++i) {
    cin >> c[i] >> w[i];
  }
  int64_t Q = P;
  constexpr int64_t kInf = 2'000'000'000'000'000'000;
  vector<vector<int64_t>> eq(N, vector<int64_t>(K + 1, kInf));
  vector<vector<int64_t>> D(K + 1, vector<int64_t>(K + 1, kInf));
  for (int i = 0; i < N; ++i) {
    if (i > 0) {
      int64_t mult = c[i] / c[i - 1];
      if (mult <= K) {
        for (int j = 0; j <= mult; ++j) {
          for (int k = 0; k <= K; ++k) {
            D[j][k] = kInf;
          }
        }
        D[0][0] = 0;
        for (int j = 1; j <= K; ++j) {
          if (eq[i - 1][j] == kInf) {
            continue;
          }
          for (int x = 1; x <= mult; ++x) {
            for (int y = j; y <= K; ++y) {
              D[x][y] = min(D[x][y], D[x - 1][y - j] + eq[i - 1][j]);
            }
          }
        }
        for (int j = 0; j <= K; ++j) {
          eq[i][j] = min(eq[i][j], D[mult][j]);
        }
      }
    }
    eq[i][1] = min(eq[i][1], w[i]);
  }
  vector<int64_t> dp(K + 1, kInf);
  vector<int64_t> nxt(K + 1, kInf);
  dp[0] = 0;
  int64_t sum = 0;
  for (int i = N - 1; i >= 0; --i) {
    sum += P / c[i];
    P %= c[i];
  }
  if (sum > K) {
    cout << "-1\n";
    return 0;
  }
  P = Q;
  vector<vector<int64_t>> dp2(K + 1, vector<int64_t>(K + 1, kInf));
  for (int i = N - 1; i >= 0; --i) {
    int64_t need = P / c[i];
    if (need > K) {
      cout << "-1\n";
      return 0;
    }
    fill(nxt.begin(), nxt.end(), kInf);
    for (int j = 0; j <= need; ++j) {
      for (int k = 0; k <= K; ++k) {
        dp2[j][k] = kInf;
      }
    }
    dp2[0][0] = 0;
    for (int j = 1; j <= K; ++j) {
      if (eq[i][j] == kInf) continue;
      for (int x = 1; x <= need; ++x) {
        for (int y = j; y <= K; ++y) {
          dp2[x][y] = min(dp2[x][y], dp2[x - 1][y - j] + eq[i][j]);
        }
      }
    }
    fill(nxt.begin(), nxt.end(), kInf);
    for (int j = 0; j <= K; ++j) {
      for (int k = 0; j + k <= K; ++k) {
        nxt[j + k] = min(nxt[j + k], dp[j] + dp2[need][k]);
      }
    }
    dp.swap(nxt);
    P %= c[i];
  }
  if (dp[K] == kInf) {
    cout << "-1\n";
    return 0;
  }
  cout << dp[K] << " ";
  fill(dp.begin(), dp.end(), -kInf);
  dp[0] = 0;
  P = Q;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j <= K; ++j) {
      eq[i][j] = -kInf;
    }
    if (i > 0) {
      int64_t mult = c[i] / c[i - 1];
      if (mult <= K) {
        for (int j = 0; j <= mult; ++j) {
          for (int k = 0; k <= K; ++k) {
            D[j][k] = -kInf;
          }
        }
        D[0][0] = 0;
        for (int j = 1; j <= K; ++j) {
          if (eq[i - 1][j] == -kInf) {
            continue;
          }
          for (int x = 1; x <= mult; ++x) {
            for (int y = j; y <= K; ++y) {
              D[x][y] = max(D[x][y], D[x - 1][y - j] + eq[i - 1][j]);
            }
          }
        }
        for (int j = 0; j <= K; ++j) {
          eq[i][j] = max(eq[i][j], D[mult][j]);
        }
      }
    }
    eq[i][1] = max(eq[i][1], w[i]);
  }
  for (int i = N - 1; i >= 0; --i) {
    int64_t need = P / c[i];
    if (need > K) {
      cout << "-1\n";
      return 0;
    }
    for (int j = 0; j <= need; ++j) {
      for (int k = 0; k <= K; ++k) {
        dp2[j][k] = -kInf;
      }
    }
    dp2[0][0] = 0;
    for (int j = 1; j <= K; ++j) {
      if (eq[i][j] == -kInf) continue;
      for (int x = 1; x <= need; ++x) {
        for (int y = j; y <= K; ++y) {
          dp2[x][y] = max(dp2[x][y], dp2[x - 1][y - j] + eq[i][j]);
        }
      }
    }
    fill(nxt.begin(), nxt.end(), -kInf);
    for (int j = 0; j <= K; ++j) {
      for (int k = 0; j + k <= K; ++k) {
        nxt[j + k] = max(nxt[j + k], dp[j] + dp2[need][k]);
      }
    }
    dp.swap(nxt);
    P %= c[i];
  }
  cout << dp[K] << "\n";
  return 0;
}

