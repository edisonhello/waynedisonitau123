#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<vector<int>> a(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> a[i][j];
    }
  }
  vector<int> row(N, 1e9);
  vector<int> col(M, 1e9);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      row[i] = min(row[i], a[i][j]);
      col[j] = min(col[j], a[i][j]);
    }
  }
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      ans += (a[i][j] == row[i]) && (a[i][j] == col[j]);
    }
  }
  cout << ans << "\n";
  return 0;
}

