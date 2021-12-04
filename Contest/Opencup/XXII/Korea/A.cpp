#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<vector<int64_t>> E(N, vector<int64_t>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> E[i][j];
    }
  }
  vector<int64_t> diff(N - 1);
  for (int i = 0; i + 1 < N; ++i) {
    diff[i] = E[0][i] - E[0][i + 1];
  }
  vector<int64_t> col(N);
  for (int i = 0; i + 1 < N - 1; ++i) {
    col[i + 1] = abs(diff[i + 1] - diff[i]) / 2;
  }
  int64_t cc = diff[0] - accumulate(col.begin() + 1, col.end(), 0LL);
  for (int i = 0; i + 1 < N; ++i) {
    diff[i] = E[i][0] - E[i + 1][0];
  }
  vector<int64_t> row(N);
  for (int i = 0; i + 1 < N - 1; ++i) {
    row[i + 1] = abs(diff[i + 1] - diff[i]) / 2;
  }
  int64_t rc = diff[0] - accumulate(row.begin() + 1, row.end(), 0LL);
  int64_t cs = 0, rs = 0;
  for (int i = 1; i < N - 1; ++i) {
    cs += col[i];
    rs += row[i];
  }
  int64_t yx = (rs + rc - cs - cc) / 2;
  int64_t s = 0, t = 0;
  for (int i = 1; i < N - 1; ++i) {
    s += i * col[i];
    s += i * row[i];
  }
  s += (N - 1) * (cc + rc);
  int64_t xy = (E[0][0] - s) / (N - 1);
  int64_t y = (xy + yx) / 2;
  int64_t x = xy - y;
  col[0] = y;
  col[N - 1] = y + cc;
  row[0] = x;
  row[N - 1] = x + rc;

  vector<vector<pair<int, int64_t>>> g(N * 2);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int64_t x = min(row[i], col[j]);
      cout << x << " ";
      row[i] -= x;
      col[j] -= x;
    }
    cout << "\n";
  }
  return 0;
}

