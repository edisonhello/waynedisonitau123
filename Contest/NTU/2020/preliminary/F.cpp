#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;


int led[51][51][51];
int red[51][51][51];
int ued[51][51][51];
int ded[51][51][51];
int drc[51][51][51][51];
int urc[51][51][51][51];
int dlc[51][51][51][51];
int ulc[51][51][51][51];

int Solve(vector<vector<int>> a) {
  int n = a.size(), m = a[0].size();
  vector<vector<int>> pref(n + 1, vector<int>(m + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      pref[i + 1][j + 1] = pref[i + 1][j] + pref[i][j + 1] - pref[i][j] + a[i][j];
    }
  }
  int res = 0;
  constexpr int kInf = 1'000'000'000;
  // vector<vector<int>> ulc(n + 1, vector<int>(m + 1, -kInf));
  // vector<vector<int>> urc(n + 1, vector<int>(m + 1, -kInf));
  // vector<vector<int>> dlc(n + 1, vector<int>(m + 1, -kInf));
  // vector<vector<int>> drc(n + 1, vector<int>(m + 1, -kInf));
  vector<int> redz(m + 1, -kInf);
  vector<int> ledz(m + 1, -kInf);
  for (int l = 0; l <= m; ++l) {
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= n; ++j) {
        led[l][i][j] = red[l][i][j] = -kInf;
      }
    }
  }
  for (int u = 0; u <= n; ++u) {
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j <= m; ++j) {
        ued[u][i][j] = ded[u][i][j] = -kInf;
      }
    }
  }

  auto Query = [&](int u, int d, int l, int r) {
    return pref[d][r] - pref[d][l] - pref[u][r] + pref[u][l];
  };

  for (int u = 0; u <= n; ++u) {
    for (int d = u; d <= n; ++d) {
      for (int l = 0; l <= m; ++l) {
        for (int r = l; r <= m; ++r) {
          int s = Query(u, d, l, r);
          led[l][u][d] = max(led[l][u][d], s);
          red[r][u][d] = max(red[r][u][d], s);
          ued[u][l][r] = max(ued[u][l][r], s);
          ded[d][l][r] = max(ded[d][l][r], s);
          // ulc[u][l] = max(ulc[u][l], s);
          // urc[u][r] = max(urc[u][r], s);
          // dlc[d][l] = max(dlc[d][l], s);
          // drc[d][r] = max(drc[d][r], s);
          redz[r] = max(redz[r], s);
          ledz[l] = max(ledz[l], s);
          res = max(res, s);
        }
      }
    }
  }
  for (int s = 1; s <= m; ++s) {
    redz[s] = max(redz[s], redz[s - 1]);
  }
  for (int s = m - 1; s >= 0; --s) {
    ledz[s] = max(ledz[s], ledz[s + 1]);
  }
  // Case 1: vertical split
  for (int s = 1; s < m; ++s) {
    res = max(res, redz[s] + ledz[s]);
  }
  static bool Z = false;
  if (!Z) {
    // Case 2: complete cross
    for (int u = 0; u < n; ++u) {
      for (int d = u + 1; d <= n; ++d) {
        for (int l = 0; l < m; ++l) {
          for (int r = l + 1; r <= m; ++r) {
            // int s = pref[d][r] - pref[d][l] - pref[u][r] + pref[u][l];
            res = max(res, ded[u][l][r] + ued[d][l][r] + red[l][u][d] + led[r][u][d]);
          }
        }
      }
    }
    Z = true;
  }
  static int D = 0;
  if (D % 2 == 0) {
    // Case 3: incomplete cross
    for (int u = 0; u < n; ++u) {
      for (int d = u + 1; d <= n; ++d) {
        for (int l = 0; l < m; ++l) {
          for (int r = l + 1; r <= m; ++r) {
            int up = ded[u][l][r];
            for (int bot = d; bot <= n; ++bot) {
              int x = red[l][u][bot];
              int y = led[r][u][bot];
              res = max(res, up + x + y + Query(d, bot, l, r));
            }
            int down = ued[d][l][r];
            for (int top = u; top >= 0; --top) {
              int x = red[l][top][d];
              int y = led[r][top][d];
              res = max(res, down + x + y + Query(top, u, l, r));
            }
          }
        }
      }
    }
  }
  D++;

  static int C = 0;
  if (C < 2) {
    C++;
    for (int i = 0; i <= 50; ++i) {
      for (int j = 0; j <= 50; ++j) {
        for (int k = 0; k <= 50; ++k) {
          for (int l = 0; l <= 50; ++l) {
            drc[i][j][k][l] = -kInf;
            ulc[i][j][k][l] = -kInf;
            dlc[i][j][k][l] = -kInf;
            urc[i][j][k][l] = kInf;
          }
        }
      }
    }
    for (int d = 0; d <= n; ++d) {
      for (int r = 0; r <= m; ++r) {
        for (int l = 0; l <= r; ++l) {
          for (int u = 0; u <= d; ++u) {
            int s = Query(u, d, l, r);
            drc[d][r][l][u] = s;
            if (u > 0) {
              drc[d][r][l][u] = max(drc[d][r][l][u], drc[d][r][l][u - 1]);
            }
          }
        }
      }
    }
    for (int u = 0; u <= n; ++u) {
      for (int l = 0; l <= m; ++l) {
        for (int r = l; r <= m; ++r) {
          for (int d = n; d >= u; --d) {
            int s = Query(u, d, l, r);
            ulc[u][l][r][d] = s;
            if (d + 1 <= n) {
              ulc[u][l][r][d] = max(ulc[u][l][r][d], ulc[u][l][r][d + 1]);
            }
          }
        }
      }
    }
    // Case 4: corner
    for (int u = 0; u < n; ++u) {
      for (int d = u + 1; d <= n; ++d) {
        for (int l = 0; l < m; ++l) {
          for (int r = l + 1; r <= m; ++r) {
            int x = -kInf, y = -kInf;
            for (int e = l; e >= 0; --e) {
              x = max(x, drc[d][r][e][u]);
            }
            for (int e = r; e <= m; ++e) {
              y = max(y, ulc[u][l][e][d]);
            }
            res = max(res, x + y - 2 * Query(u, d, l, r));
          }
        }
      }
    }
  }
  static bool J = false;
  if (!J) {
    // Case 5: contained
    for (int d = 0; d <= n; ++d) {
      for (int l = 0; l <= m; ++l) {
        for (int r = l; r <= m; ++r) {
          for (int u = 0; u <= d; ++u) {
            int s = Query(u, d, l, r);
            dlc[d][l][r][u] = s;
            if (u > 0) {
              dlc[d][l][r][u] = max(dlc[d][l][r][u], dlc[d][l][r][u - 1]);
            }
          }
        }
      }
    }
    for (int u = 0; u <= n; ++u) {
      for (int r = 0; r <= m; ++r) {
        for (int l = 0; l <= r; ++l) {
          for (int d = u; d <= n; ++d) {
            int s = Query(u, d, l, r);
            urc[u][r][l][d] = s;
            if (d > u) {
              urc[u][r][l][d] = min(urc[u][r][l][d], urc[u][r][l][d - 1]);
            }
          }
        }
      }
    }
    for (int u = 0; u <= n; ++u) {
      for (int d = u; d <= n; ++d) {
        for (int l = 0; l <= m; ++l) {
          for (int r = l; r <= m; ++r) {
            int x = -kInf, y = kInf;
            for (int e = r; e <= m; ++e) {
              x = max(x, dlc[d][l][e][u]);
            }
            for (int e = l; e <= r; ++e) {
              y = min(y, urc[u][r][e][d]);
            }
            res = max(res, x - y);
          }
        }
      }
    }
    J = true;
  }
  return res;
}

vector<vector<int>> Rotate(vector<vector<int>> a) {
  int n = a.size(), m = a[0].size();
  vector<vector<int>> res(m, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      res[j][n - 1 - i] = a[i][j];
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  int ans = 0;
  for (int i = 0; i < 4; ++i) {
    ans = max(ans, Solve(a));
    a = Rotate(a);
  }
  cout << ans << "\n";
  return 0;
}
