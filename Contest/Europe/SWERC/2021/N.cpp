#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<vector<int>> A(N, vector<int>(N));
  vector<pair<int, int>> where(N * N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> A[i][j];
      A[i][j]--;
      where[A[i][j]] = {i, j};
    }
  }
  vector<int> row(N), col(N);
  int64_t s = 0;
  for (int i = N * N - 1; i >= 0; --i) {
    auto [r, c] = where[i];
    s += 1LL * row[r] * col[c];
    row[r]++;
    col[c]++;
  }
  int64_t t = 1LL * N * (N - 1) / 2 * N * (N - 1) / 2;
  cout << t - (s - t) << "\n";
}

