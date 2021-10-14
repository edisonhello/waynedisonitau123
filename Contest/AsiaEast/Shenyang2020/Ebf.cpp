#include <bits/stdc++.h>
using namespace std;

int main() {
  int M;
  cin >> M;
  vector<vector<int>> p(M);
  for (int i = 0; i < M; ++i) {
    int K;
    cin >> K;
    p[i].resize(K);
    for (int j = 0; j < K; ++j) {
      cin >> p[i][j];
    }
  }
  int A;
  cin >> A;
  vector<int> B(M + 1);
  for (int i = 1; i <= M; ++i) cin >> B[i];
  int64_t res = 1'000'000'000'000'000;
  vector<int> ans;
  for (int X = 1; X <= 100; ++X) {
    vector<int> load(1000);
    int64_t cost = 0;
    for (int i = 0; i < M; ++i) {
      int last = -1;
      vector<bool> hold(1000);
      for (int j = 0; j < p[i].size(); ++j) {
        if (last == -1 || p[i][j] - last >= X) {
          load[p[i][j]]++;
        }
        last = p[i][j];
        for (int k = 0; k < X; ++k) {
          if (!hold[p[i][j] + k]) cost += A;
          hold[p[i][j] + k] = true;
        }
      }
    }
    for (int i = 0; i < 1000; ++i) {
      cost += load[i] * B[load[i]];
    }
    if (cost < res) {
      res = cost;
      ans = {X};
    } else if (cost == res) {
      ans.push_back(X);
    }
  }
  cout << res << " " << ans.size() << "\n";
  for (int u : ans) cout << u << " ";
  cout << "\n";
}
