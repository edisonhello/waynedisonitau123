#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N * M; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    grid[x][y] = i;
  }
  vector<int> col(M);
  vector<int> left(M);
  vector<int> right(M);
  vector<int64_t> res(N * M);

  for (int i = 0; i < N; ++i) {
    fill(col.begin(), col.end(), N * M);
    for (int j = i; j < N; ++j) {
      for (int k = 0; k < M; ++k) {
        col[k] = min(col[k], grid[j][k]);
        left[k] = k - 1;
        right[k] = k + 1;
      }
      for (int k = 0; k < M; ++k) {
        while (left[k] >= 0 && col[k] < col[left[k]]) left[k] = left[left[k]];
      }
      for (int k = M - 1; k >= 0; --k) {
        while (right[k] < M && col[k] < col[right[k]]) right[k] = right[right[k]];
      }
      for (int k = 0; k < M; ++k) {
        res[col[k]] += 1LL * (k - left[k]) * (right[k] - k);
      }
    }
  }
  int64_t total = 1LL * N * (N + 1) / 2 * M * (M + 1) / 2;
  for (int i = 0; i < N * M; ++i) {
    total -= res[i];
    cout << total << "\n";
  }
  return 0;
}
