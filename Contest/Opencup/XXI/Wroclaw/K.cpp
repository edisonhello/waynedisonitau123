#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N, K;
    cin >> N >> K;
    int M = N + K;
    constexpr int kInf = 1'000'000'000;
    vector<vector<int>> dist(M, vector<int>(M, kInf));
    for (int i = 0; i < M; ++i) dist[i][i] = 0;
    vector<vector<int>> route(K);
    for (int i = 0; i < K; ++i) {
      int r;
      cin >> r;
      route[i].resize(r);
      for (int j = 0; j < r; ++j) {
        cin >> route[i][j];
        route[i][j]--;
        dist[route[i][j]][i + N] = 1;
        dist[i + N][route[i][j]] = 1;
      }
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    vector<bool> used(K);
    int S;
    cin >> S;
    vector<int> rev(S);
    for (int i = 0; i < S; ++i) {
      cin >> rev[i];
      rev[i]--;
      used[rev[i]] = true;
    }
    for (int i = 0; i < K; ++i) {
      if (!used[i]) order.push_back(i + N);
    }
    reverse(rev.begin(), rev.end());
    for (int u : rev) order.push_back(u + N);
    vector<int> ans;
    assert(order.size() == M);
    for (int it = 0; it < M; ++it) {
      int u = order[it];
      for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
          dist[i][j] = min(dist[i][j], dist[i][u] + dist[u][j]);
        }
      }
      if (M - it - 1 <= S) {
        int vd = 0;
        for (int i = 0; i < N; ++i) {
          for (int j = 0; j < N; ++j) {
            if (dist[i][j] == kInf) continue;
            vd = max(vd, dist[i][j]);
          }
        }
        ans.push_back((vd - 2) / 2);
      }
    }
    reverse(ans.begin(), ans.end());
    for (int u : ans) cout << u << "\n";
  }
}
