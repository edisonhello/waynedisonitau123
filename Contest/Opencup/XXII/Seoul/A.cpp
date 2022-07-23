#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K, M;
  cin >> N >> K >> M;
  vector<int> c(N);
  for (int i = 0; i < N; ++i) {
    cin >> c[i];
    c[i]--;
  }
  vector<int> mask(M);
  for (int i = 0; i < M; ++i) {
    int r;
    cin >> r;
    for (int j = 0; j < r; ++j) {
      int k;
      cin >> k;
      mask[i] |= (1 << (k - 1));
    }
  }
  queue<pair<int, int>> que;
  vector<vector<int>> dist(1 << N, vector<int>(1 << M, -1));
  int init = 0;
  for (int i = 0; i < N; ++i) {
    if (c[i] == 0) {
      init |= (1 << i);
    }
  }
  que.emplace(init, 0);
  dist[init][0] = 0;
  while (!que.empty()) {
    auto [x, y] = que.front();
    if (x == (1 << N) - 1 && y == 0) {
      cout << dist[x][y] << "\n";
      return 0;
    }
    que.pop();
    for (int i = 0; i < M; ++i) {
      if (dist[x][y ^ (1 << i)] == -1) {
        dist[x][y ^ (1 << i)] = dist[x][y] + 1;
        que.emplace(x, y ^ (1 << i));
      }
    }
    int cover = 0;
    for (int i = 0; i < M; ++i) {
      if (y >> i & 1) {
        cover |= mask[i];
      }
    }
    for (int k = 0; k < K; ++k) {
      int nx = 0;
      for (int i = 0; i < N; ++i) {
        if (cover >> i & 1) {
          if (x >> i & 1) {
            nx |= (1 << i);
          }
        } else {
          if (c[i] == k) {
            nx |= (1 << i);
          }
        }
      }
      if (dist[nx][y] == -1) {
        dist[nx][y] = dist[x][y] + 1;
        que.emplace(nx, y);
      }
    }
  }
  cout << "-1\n";
  return 0;
}
