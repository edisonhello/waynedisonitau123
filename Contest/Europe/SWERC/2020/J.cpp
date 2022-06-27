#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, C;
  cin >> N >> M >> C;
  vector<vector<int>> to(N, vector<int>(C, -1));
  vector<vector<vector<int>>> from(N, vector<vector<int>>(C));
  vector<int> mask(N);
  for (int i = 0; i < M; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    to[u][c] = v;
    from[v][c].push_back(u);
    mask[u] |= (1 << c);
  }

  vector<vector<vector<bool>>> dp(N, vector<vector<bool>>(N, vector<bool>(C + 1)));
  vector<tuple<int, int, int>> que;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j <= C; ++j) {
      dp[i][i][j] = true;
      que.emplace_back(i, i, j);
    }
  }
  for (int iter = 0; iter < que.size(); ++iter) {
    auto [x, y, c] = que[iter];
    // dp[i][j][f] =
    //   mask[i] & f = 0 and
    //   or_{c} dp[x][y][c]
    // cerr << "x = " << x << " y = " << y << " c = " << c << endl;
    if (c < C) {
      if (to[y][c] != -1 && !from[x][c].empty()) {
        for (int z : from[x][c]) {
          for (int f = 0; f <= C; ++f) {
            if (mask[z] >> f & 1) {
              continue;
            }
            if (!dp[z][to[y][c]][f]) {
              dp[z][to[y][c]][f] = true;
              que.emplace_back(z, to[y][c], f);
            }
          }
        }
      }
    }
    // dp[i][j][f] = 
    //   mask[i] & f = 0 and
    //   or_{k} dp[i][k][f] and dp[k][j][f]
    for (int i = 0; i < N; ++i) {
      if (mask[i] >> c & 1) {
        continue;
      }
      if (dp[i][x][c] && !dp[i][y][c]) {
        dp[i][y][c] = true;
        que.emplace_back(i, y, c);
      }
    }
    if ((mask[x] >> c & 1) == 0) {
      for (int i = 0; i < N; ++i) {
        if (dp[y][i][c] && !dp[x][i][c]) {
          dp[x][i][c] = true;
          que.emplace_back(x, i, c);
        }
      }
    }
    // for (int z = 0; z < N; ++z) {
    //   if (dp[z][x][c]) {
    //     if (!dp[z][y][c]) {
    //       dp[z][y][c] = true;
    //       que.emplace_back(z, y, c);
    //     }
    //   }
    // }
  }
  vector<vector<vector<bool>>> good(N, vector<vector<bool>>(N, vector<bool>(C + 1)));
  {
    for (int s = 0; s < N; ++s) {
      good[s][s][C] = true;
      vector<pair<int, int>> que = {{s, C}};
      for (int it = 0; it < que.size(); ++it) {
        auto [x, c] = que[it];
        if (mask[x] >> c & 1) {
          continue;
        }
        for (int j = 0; j < C; ++j) {
          if (to[x][j] != -1) {
            if (!good[s][to[x][j]][j]) {
              good[s][to[x][j]][j] = true;
              que.emplace_back(to[x][j], j);
            }
          }
        }
        for (int y = 0; y < N; ++y) {
          if (dp[x][y][c]) {
            if (!good[s][y][c]) {
              good[s][y][c] = true;
              que.emplace_back(y, c);
            }
          }
        }
      }
    }
  }
  int ans = N + 1;
  for (int s = 0; s < N; ++s) {
    bool ok = false;
    for (int j = 0; j <= C; ++j) {
      if (good[s][N - 1][j]) {
        ok = true;
      }
    }
    if (!ok) {
      continue;
    }
    vector<vector<int>> dist(N, vector<int>(C + 1, N + 1));
    vector<vector<bool>> vis(N, vector<bool>(C + 1));
    dist[s][C] = 0;
    priority_queue<tuple<int, int, int>> pq;
    pq.emplace(0, s, C);
    while (!pq.empty()) {
      auto [d, x, c] = pq.top();
      pq.pop();
      if (vis[x][c]) {
        continue;
      }
      vis[x][c] = true;
      for (int y = 0; y < N; ++y) {
        if (dp[y][x][c] && dist[y][c] > dist[x][c]) {
          dist[y][c] = dist[x][c];
          pq.emplace(-dist[y][c], y, c);
        }
      }
      for (int k = 0; k < C; ++k) {
        for (int y : from[x][k]) {
          if (dist[y][k] > dist[x][c] + 1) {
            dist[y][k] = dist[x][c] + 1;
            pq.emplace(-dist[y][k], y, k);
          }
        }
      }
    }
    for (int i = 0; i <= C; ++i) {
      ans = min(ans, dist[0][i]);
    }
  }
  cout << ans << "\n";
  return 0;
}
