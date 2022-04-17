#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Q;
  cin >> N >> Q;
  vector<string> grid(N);
  for (int i = 0; i < N; ++i) {
    cin >> grid[i];
  }
  vector<int> col(N);
  vector<int> row(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      col[j] += grid[i][j] == '1';
      row[i] += grid[i][j] == '1';
    }
  }
  vector<deque<int>> dq(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      dq[i].push_back(grid[i][j] == '1');
    }
  }
  while (Q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int i, j, b;
      cin >> i >> j >> b;
      i--;
      j--;
      col[j] -= dq[i][j] == 1;
      row[i] -= dq[i][j] == 1;
      dq[i][j] = b;
      col[j] += dq[i][j] == 1;
      row[i] += dq[i][j] == 1;
    } else {
      int b;
      cin >> b;
      // col[0] -= dq[0][0] == 1;
      // row[0] -= dq[0][0] == 1;
      col[N - 1] -= dq[N - 1][N - 1] == 1;
      // row[N - 1] -= dq[N - 1][N - 1] == 1;
      vector<int> new_col(N);
      for (int i = 0; i < N; ++i) {
        new_col[i] = col[(i + N - 1) % N];
      }
      for (int i = 0; i < N; ++i) {
        int b = dq[i].back();
        dq[i].pop_back();
        row[i] -= b == 1;
        if (i + 1 < N) {
          dq[i + 1].push_front(b);
          row[i + 1] += b == 1;
        }
      }
      dq[0].push_front(b);
      col = new_col;
      col[0] += dq[0][0] == 1;
      row[0] += dq[0][0] == 1;
      // col[N - 1] += dq[N - 1][N - 1] == 1;
      // row[N - 1] += dq[N - 1][N - 1] == 1;
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
      ans += col[i] == N;
      ans += row[i] == N;
    }
    cout << ans << "\n";
  }
  return 0;
}
