#include <bits/stdc++.h>
using namespace std;

int64_t sp[30][30][10][10];

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cin >> A[i][j];
  }
  vector<vector<int64_t>> sum(N + 1, vector<int64_t>(M));
  for (int j = 0; j < M; ++j) {
    for (int i = 0; i < N; ++i) {
      sum[i + 1][j] = sum[i][j] + A[i][j];
    }
  }
  int R = -1, C = -1;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (A[i][j] == -1) {
        R = i;
        C = j;
      }
    }
  }
  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  vector<vector<int64_t>> dp(N, vector<int64_t>(N, kInf));
  for (int i = 0; i < N; ++i) {
    for (int j = i + 2; j < N; ++j) dp[i][j] = sum[j + 1][0] - sum[i][0];
  }
  for (int c = 1; c <= C; ++c) {
    vector<vector<int64_t>> ndp(N, vector<int64_t>(N, kInf));

    auto Query = [&](int l, int r, int u, int d) {
      int s = 31 - __builtin_clz(r - l);
      int t = 31 - __builtin_clz(d - u);
      return min(
          min(sp[l][u][s][t], sp[r - (1 << s)][u][s][t]),
          min(sp[l][d - (1 << t)][s][t], sp[r - (1 << s)][d - (1 << t)][s][t]));
    };

    {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (c == C && (i >= R || j <= R)) sp[i][j][0][0] = kInf;
          else sp[i][j][0][0] = dp[i][j] - sum[i][c] + sum[j + 1][c];
        }
      }
      for (int s = 0; (1 << s) <= N; ++s) {
        for (int t = 0; (1 << t) <= N; ++t) {
          if (s == 0 && t == 0) continue;
          if (s > 0) {
            for (int i = 0; i + (1 << s) <= N; ++i) {
              for (int j = 0; j < N; ++j) {
                sp[i][j][s][t] =
                    min(sp[i][j][s - 1][t], sp[i + (1 << (s - 1))][j][s - 1][t]);
              }
            }
          }
          if (t > 0) {
            for (int j = 0; j + (1 << t) <= N; ++j) {
              for (int i = 0; i < N; ++i) {
                sp[i][j][s][t] =
                    min(sp[i][j][s][t - 1], sp[i][j + (1 << (t - 1))][s][t - 1]);
              }
            }
          }
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          int64_t v = Query(0, i + 1, j, N) + sum[i + 1][c] - sum[j][c];
          ndp[i][j] = min(ndp[i][j], v);
        }
      }
    }
    {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (c == C && (i >= R || j <= R)) sp[i][j][0][0] = kInf;
          else sp[i][j][0][0] = dp[i][j] - sum[i][c] - sum[j][c];
        }
      }
      for (int s = 0; (1 << s) <= N; ++s) {
        for (int t = 0; (1 << t) <= N; ++t) {
          if (s == 0 && t == 0) continue;
          if (s > 0) {
            for (int i = 0; i + (1 << s) <= N; ++i) {
              for (int j = 0; j < N; ++j) {
                sp[i][j][s][t] =
                    min(sp[i][j][s - 1][t], sp[i + (1 << (s - 1))][j][s - 1][t]);
              }
            }
          }
          if (t > 0) {
            for (int j = 0; j + (1 << t) <= N; ++j) {
              for (int i = 0; i < N; ++i) {
                sp[i][j][s][t] =
                    min(sp[i][j][s][t - 1], sp[i][j + (1 << (t - 1))][s][t - 1]);
              }
            }
          }
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          int64_t v = Query(0, i + 1, i, j + 1) + sum[i + 1][c] + sum[j + 1][c];
          ndp[i][j] = min(ndp[i][j], v);
        }
      }
    }
    {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (c == C && (i >= R || j <= R)) sp[i][j][0][0] = kInf;
          else sp[i][j][0][0] = dp[i][j] + sum[i + 1][c] + sum[j + 1][c];
        }
      }
      for (int s = 0; (1 << s) <= N; ++s) {
        for (int t = 0; (1 << t) <= N; ++t) {
          if (s == 0 && t == 0) continue;
          if (s > 0) {
            for (int i = 0; i + (1 << s) <= N; ++i) {
              for (int j = 0; j < N; ++j) {
                sp[i][j][s][t] =
                    min(sp[i][j][s - 1][t], sp[i + (1 << (s - 1))][j][s - 1][t]);
              }
            }
          }
          if (t > 0) {
            for (int j = 0; j + (1 << t) <= N; ++j) {
              for (int i = 0; i < N; ++i) {
                sp[i][j][s][t] =
                    min(sp[i][j][s][t - 1], sp[i][j + (1 << (t - 1))][s][t - 1]);
              }
            }
          }
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          int64_t v = Query(i, j + 1, j, N) - sum[i][c] - sum[j][c];
          ndp[i][j] = min(ndp[i][j], v);
        }
      }
    }
    {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (c == C && (i >= R || j <= R)) sp[i][j][0][0] = kInf;
          else sp[i][j][0][0] = dp[i][j] + sum[i + 1][c] - sum[j][c];
        }
      }
      for (int s = 0; (1 << s) <= N; ++s) {
        for (int t = 0; (1 << t) <= N; ++t) {
          if (s == 0 && t == 0) continue;
          if (s > 0) {
            for (int i = 0; i + (1 << s) <= N; ++i) {
              for (int j = 0; j < N; ++j) {
                sp[i][j][s][t] =
                    min(sp[i][j][s - 1][t], sp[i + (1 << (s - 1))][j][s - 1][t]);
              }
            }
          }
          if (t > 0) {
            for (int j = 0; j + (1 << t) <= N; ++j) {
              for (int i = 0; i < N; ++i) {
                sp[i][j][s][t] =
                    min(sp[i][j][s][t - 1], sp[i][j + (1 << (t - 1))][s][t - 1]);
              }
            }
          }
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          int64_t v = Query(i, j + 1, i, j + 1) - sum[i][c] + sum[j + 1][c];
          ndp[i][j] = min(ndp[i][j], v);
        }
      }
    }
    if (c != C) {
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          ndp[i][j] = min(ndp[i][j], sum[j + 1][c] - sum[i][c]);
        }
      }
    }
    dp = ndp;
  }
  for (int i = 0; i < N; ++i) {
    for (int j = i + 2; j < N; ++j) {
      if (!(i < R && R < j)) dp[i][j] = kInf;
    }
  }
  int64_t ans = kInf;
  for (int c = C + 1; c < N; ++c) {
    vector<vector<int64_t>> ndp(N, vector<int64_t>(N, kInf));
    {
      vector<vector<int64_t>> cdp(N, vector<int64_t>(N, kInf));
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          cdp[i][j] = dp[i][j] + A[i][c] + A[j][c];
          if (i > 0) cdp[i][j] = min(cdp[i][j], cdp[i - 1][j] + A[i][c]);
          if (j > 0) cdp[i][j] = min(cdp[i][j], cdp[i][j - 1] + A[j][c]);
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          ndp[i][j] = min(ndp[i][j], cdp[i][j]);
        }
      }
    }
    {
      vector<vector<int64_t>> cdp(N, vector<int64_t>(N, kInf));
      for (int i = 0; i < N; ++i) {
        for (int j = N - 1; j >= i + 2; --j) {
          cdp[i][j] = dp[i][j] + A[i][c] + A[j][c];
          if (i > 0) cdp[i][j] = min(cdp[i][j], cdp[i - 1][j] + A[i][c]);
          if (j + 1 < N) cdp[i][j] = min(cdp[i][j], cdp[i][j + 1] + A[j][c]);
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          ndp[i][j] = min(ndp[i][j], cdp[i][j]);
        }
      }
    }
    {
      vector<vector<int64_t>> cdp(N, vector<int64_t>(N, kInf));
      for (int i = N - 1; i >= 0; --i) {
        for (int j = i + 2; j < N; ++j) {
          cdp[i][j] = dp[i][j] + A[i][c] + A[j][c];
          if (i + 1 < N) cdp[i][j] = min(cdp[i][j], cdp[i + 1][j] + A[i][c]);
          if (j > 0) cdp[i][j] = min(cdp[i][j], cdp[i][j - 1] + A[j][c]);
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          ndp[i][j] = min(ndp[i][j], cdp[i][j]);
        }
      }
    }
    {
      vector<vector<int64_t>> cdp(N, vector<int64_t>(N, kInf));
      for (int i = N - 1; i >= 0; --i) {
        for (int j = N - 1; j >= i + 2; --j) {
          cdp[i][j] = dp[i][j] + A[i][c] + A[j][c];
          if (i + 1 < N) cdp[i][j] = min(cdp[i][j], cdp[i + 1][j] + A[i][c]);
          if (j + 1 < N) cdp[i][j] = min(cdp[i][j], cdp[i][j + 1] + A[j][c]);
        }
      }
      for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {
          ndp[i][j] = min(ndp[i][j], cdp[i][j]);
        }
      }
    }
    for (int i = 0; i < N; ++i) {
      for (int j = i + 2; j < N; ++j) {
        ans = min(ans, ndp[i][j] + sum[j][c] - sum[i + 1][c]);
      }
    }
    dp = ndp;
  }
  cout << ans << "\n";
  return 0;
}
