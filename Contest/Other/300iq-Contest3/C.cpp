#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<string> grid(N);
  int free_cells = 0;
  for (int i = 0; i < N; ++i) {
    cin >> grid[i];
    free_cells += count(grid[i].begin(), grid[i].end(), '.');
  }
  vector<vector<int>> from_top(N, vector<int>(M, -1));
  vector<vector<int>> from_down(N, vector<int>(M, -1));
  vector<vector<int>> to_top(N, vector<int>(M, -1));
  vector<vector<int>> to_down(N, vector<int>(M, -1));
  from_top[0][0] = from_down[0][0] = (grid[0][0] == '.' ? 0 : -1);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (grid[i][j] == '.') {
        if (i > 0 && from_top[i - 1][j] != -1) {
          from_top[i][j] = 0;
        } else if (j > 0 && from_top[i][j - 1] != -1) {
          from_top[i][j] = 1;
        }
        if (j > 0 && from_down[i][j - 1] != -1) {
          from_down[i][j] = 1;
        } else if (i > 0 && from_down[i - 1][j] != -1) {
          from_down[i][j] = 0;
        }
      }
    }
  }
  if (from_top[N - 1][M - 1] == -1) {
    cout << 1LL * free_cells * (free_cells - 1) / 2 << "\n";
    return 0;
  }
  to_top[N - 1][M - 1] = to_down[N - 1][M - 1] = 0;
  for (int i = N - 1; i >= 0; --i) {
    for (int j = M - 1; j >= 0; --j) {
      if (grid[i][j] == '.') {
        if (j + 1 < M && to_top[i][j + 1] != -1) {
          to_top[i][j] = 1;
        } else if (i + 1 < N && to_top[i + 1][j] != -1) {
          to_top[i][j] = 0;
        }
        if (i + 1 < N && to_down[i + 1][j] != -1) {
          to_down[i][j] = 0;
        } else if (j + 1 < M && to_down[i][j + 1] != -1) {
          to_down[i][j] = 1;
        }
      }
    }
  }
  vector<vector<bool>> top_path(N, vector<bool>(M)), down_path(N, vector<bool>(M));
  top_path[0][0] = down_path[0][0] = true;
  for (int i = N - 1, j = M - 1; i > 0 || j > 0;) {
    top_path[i][j] = true;
    if (from_top[i][j] == 0) {
      i--;
    } else {
      j--;
    }
  }
  for (int i = N - 1, j = M - 1; i > 0 || j > 0;) {
    down_path[i][j] = true;
    if (from_down[i][j] == 0) {
      i--;
    } else {
      j--;
    }
  }
  int cut = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cut += top_path[i][j] && down_path[i][j];
    }
  }
  int64_t pairs = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (top_path[i][j] && !down_path[i][j]) {
        int s = i + j;
        for (int k = i + 1; k < N; ++k) {
          int l = s - k;
          if (l >= 0 && l < M) {
            if (to_top[k][l] != -1) {
              int x = k, y = l, blocks = 0;
              while (x > 0 || y > 0) {
                if (down_path[x][y] && !top_path[x][y]) {
                  blocks++;
                }
                if (from_top[x][y] == 0) {
                  x--;
                } else {
                  y--;
                }
              }
              x = k;
              y = l;
              while (x < N - 1 || y < M - 1) {
                if (x != k || y != l) {
                  if (down_path[x][y] && !top_path[x][y]) {
                    blocks++;
                  }
                }
                if (to_top[x][y] == 0) {
                  x++;
                } else {
                  y++;
                }
              }
              pairs += blocks;
              break;
            }
          }
        }
      }
      if (down_path[i][j] && !top_path[i][j]) {
        int s = i + j;
        for (int k = i - 1; k >= 0; --k) {
          int l = s - k;
          if (l >= 0 && l < M) {
            if (to_down[k][l] != -1) {
              int x = k, y = l, blocks = 0;
              while (x > 0 || y > 0) {
                if (top_path[x][y] && !down_path[x][y]) {
                  blocks++;
                }
                if (from_down[x][y] == 0) {
                  x--;
                } else {
                  y--;
                }
              }
              x = k;
              y = l;
              while (x < N - 1 || y < M - 1) {
                if (x != k || y != l) {
                  if (top_path[x][y] && !down_path[x][y]) {
                    blocks++;
                  }
                }
                if (to_down[x][y] == 0) {
                  x++;
                } else {
                  y++;
                }
              }
              pairs += blocks;
              break;
            }
          }
        }
      }
    }
  }
  int64_t ans = pairs / 2;
  ans += 1LL * cut * (free_cells - 1);
  ans -= 1LL * cut * (cut - 1) / 2;
  cout << ans << "\n";
}
