#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> A(N);
  vector<int> B(M);
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < M; ++i) cin >> B[i];

  constexpr int kP = 998244353;

  auto Get = [&](const vector<int> &A) {
    int N = A.size();
    vector<vector<int>> dp(N + 1, vector<int>(N + 1));
    vector<vector<int>> sdp(N + 1, vector<int>(N + 1));
    vector<int> nxt(100 + 1, -1);
    dp[N][0] = 1;
    for (int i = 0; i <= N; ++i) sdp[i][0] = 1;
    for (int i = N - 1; i >= 0; --i) {
      for (int j = 1; j <= N; ++j) {
        dp[i][j] = sdp[i + 1][j - 1];
        if (nxt[A[i]] != -1) {
          (dp[i][j] += kP - sdp[nxt[A[i]] + 1][j - 1]) %= kP;
        }
        sdp[i][j] = (dp[i][j] + sdp[i + 1][j]) % kP;
      }
      nxt[A[i]] = i;
    }
    return dp;
  };

  auto GetPrv = [&](const vector<int> &A) {
    vector<int> prv(100 + 1, -1), res(A.size());
    for (int i = 0; i < A.size(); ++i) {
      res[i] = prv[A[i]];
      prv[A[i]] = i;
    }
    return res;
  };

  auto D1 = Get(A), D2 = Get(B);
  vector<int> C1(N + 1), C2(M + 1);
  for (int i = 0; i < N; ++i) {
    for (int j = 1; j <= N; ++j) (C1[j] += D1[i][j]) %= kP;
  }
  for (int i = 0; i < M; ++i) {
    for (int j = 1; j <= M; ++j) (C2[j] += D2[i][j]) %= kP;
  }
  int sum = 0, res = 0;
  for (int L = 1; L <= N; ++L) {
    res += 1LL * C1[L] * sum % kP;
    res %= kP;
    if (L <= M) (sum += C2[L]) %= kP;
  }
  vector<vector<int>> dp(N + 1, vector<int>(M + 1));
  vector<vector<int>> sdp(N + 1, vector<int>(M + 1));
  vector<int> P1 = GetPrv(A), P2 = GetPrv(B);
  dp[0][0] = 1;
  for (int i = 0; i <= N; ++i) sdp[i][0] = 1;
  for (int i = 0; i <= M; ++i) sdp[0][i] = 1;
  // vector<vector<int>> suff(N + 1, vector<int>(M + 1));
  // for (int i = N - 1; i >= 0; --i) {
  //   for (int j = 1; j <= N; ++j) (D1[i][j] += D1[i + 1][j]) %= kP;
  // }
  // for (int i = M - 1; i >= 0; --i) {
  //   for (int j = 1; j <= M; ++j) (D2[i][j] += D2[i + 1][j]) %= kP;
  // }
  // vector<int> K1(N + 1), K2(M + 1);
  // for (int i = 0; i <= N; ++i) {
  //   for (int j = 1; j <= N; ++j) (K1[i] += D1[i][j]) %= kP;
  // }
  // for (int i = 0; i <= M; ++i) {
  //   for (int j = 1; j <= M; ++j) (K2[i] += D2[i][j]) %= kP;
  // }
  // for (int i = N; i >= 0; --i) {
  //   for (int j = M; j >= 0; --j) {
  //     suff[i][j] = 1LL * (K1[i] + 1) * (K2[j] + 1) % kP;
  //   }
  // }

  auto GetSum = [&](int l, int r, int u, int d) {
    assert(l <= r && u <= d);
    int res = sdp[r][d];
    if (l > 0) (res += kP - sdp[l - 1][d]) %= kP;
    if (u > 0) (res += kP - sdp[r][u - 1]) %= kP;
    if (l > 0 && u > 0) (res += sdp[l - 1][u - 1]) %= kP;
    return res;
  };

  auto GetNxt = [&](const vector<int> &A) {
    vector<int> nxt(100 + 1, A.size()), res(A.size());
    for (int i = A.size() - 1; i >= 0; --i) {
      res[i] = nxt[A[i]];
      nxt[A[i]] = i;
    }
    return res;
  };

  vector<vector<int>> dp2(N + 1, vector<int>(M + 1));
  vector<vector<int>> sdp2(N + 1, vector<int>(M + 1));

  auto GetSum2 = [&](int l, int r, int u, int d) {
    assert(l <= r && u <= d);
    int res = sdp2[l][u];
    if (r + 1 <= N) (res += kP - sdp2[r + 1][u]) %= kP;
    if (d + 1 <= M) (res += kP - sdp2[l][d + 1]) %= kP;
    if (r + 1 <= N && d + 1 <= M) (res += sdp2[r + 1][d + 1]) %= kP;
    return res;
  };

  vector<int> Q1 = GetNxt(A), Q2 = GetNxt(B);
  dp2[N][M] = 1;
  for (int i = 0; i <= N; ++i) sdp2[i][M] = 1;
  for (int i = 0; i <= M; ++i) sdp2[N][i] = 1;

  for (int i = N - 1; i >= 0; --i) {
    for (int j = M - 1; j >= 0; --j) {
      int x = Q1[i], y = Q2[j];
      int v = GetSum2(i + 1, x, j + 1, y);
      dp2[i][j] = v;
      sdp2[i][j] = (0LL + sdp2[i + 1][j] + sdp2[i][j + 1] + dp2[i][j] + kP - sdp2[i + 1][j + 1]) % kP;
    }
  }

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      int x = P1[i - 1], y = P2[j - 1];
      int v = GetSum(x + 1, i - 1, y + 1, j - 1);
      if (A[i - 1] == B[j - 1]) {
        dp[i][j] = v;
      } else {
        if (A[i - 1] > B[j - 1]) {
          res += 1LL * v * sdp2[i][j] % kP;
          res %= kP;
        }
      }
      sdp[i][j] = (0LL + sdp[i - 1][j] + sdp[i][j - 1] + dp[i][j] + kP - sdp[i - 1][j - 1]) % kP;
    }
  }
  cout << res << "\n";
  return 0;
}
