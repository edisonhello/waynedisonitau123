#include <bits/stdc++.h>
using namespace std;

int main() {
  int H, W;
  cin >> H >> W;
  vector<vector<int>> a(H, vector<int>(W));
  vector<vector<int>> b(H, vector<int>(W));
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) cin >> a[i][j];
  }
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) cin >> b[i][j];
  }

  const int N = H * W;
  vector<vector<pair<int, int>>> g(N);
  constexpr int kDx[4] = {0, 1, 0, -1};
  constexpr int kDy[4] = {1, 0, -1, 0};

  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      for (int d = 0; d < 4; ++d) {
        if (i + kDx[d] < 0 || i + kDx[d] >= H) continue;
        if (j + kDy[d] < 0 || j + kDy[d] >= W) continue;
        g[(i + kDx[d]) * W + (j + kDy[d])].emplace_back(i * W + j, b[i][j]);
        g[i * W + j].emplace_back((i + kDx[d]) * W + (j + kDy[d]), -a[i][j]);
      }
    }
  }
  vector<int> dist(N), upd(N);
  vector<bool> inque(N, true);
  queue<int> que;
  for (int i = 0; i < N; ++i) que.push(i);
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    inque[x] = false;
    for (auto [u, w] : g[x]) {
      if (dist[u] > dist[x] + w) {
        if (++upd[u] > N) {
          cout << "-1\n";
          return 0;
        }
        dist[u] = dist[x] + w;
        if (!inque[u]) {
          inque[u] = true;
          que.push(u);
        }
      }
    }
  }
  int t = *min_element(dist.begin(), dist.end());
  for (int i = 0; i < N; ++i) dist[i] -= t;
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) cout << dist[i * W + j] << " ";
    cout << "\n";
  }
}
