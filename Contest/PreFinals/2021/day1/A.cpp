#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> x1(N), y1(N), x2(N), y2(N);
  map<pair<int, int>, pair<int, int>> D;
  for (int i = 0; i < N; ++i) {
    cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    D[make_pair(x1[i], y1[i])] = make_pair(i, 0);
    D[make_pair(x2[i], y2[i])] = make_pair(i, 1);
  }

  constexpr int kDx[4] = {0, 1, 0, -1};
  constexpr int kDy[4] = {1, 0, -1, 0};

  vector<vector<int>> g(2 * N);

  for (int i = 0; i < N; ++i) {
    for (int d = 0; d < 4; ++d) {
      int nx = x1[i] + kDx[d];
      int ny = y1[i] + kDy[d];
      if (D.find(make_pair(nx, ny)) != D.end()) {
        auto p = D[make_pair(nx, ny)];
        if (p.first == i) continue;
        g[2 * i].push_back(2 * p.first + p.second);
        g[2 * p.first + p.second].push_back(2 * i);
      }
    }
    for (int d = 0; d < 4; ++d) {
      int nx = x2[i] + kDx[d];
      int ny = y2[i] + kDy[d];
      if (D.find(make_pair(nx, ny)) != D.end()) {
        auto p = D[make_pair(nx, ny)];
        if (p.first == i) continue;
        g[2 * i + 1].push_back(2 * p.first + p.second);
        g[2 * p.first + p.second].push_back(2 * i + 1);
      }
    }
  }

  vector<int> match(2 * N, -1);
  vector<bool> vis(2 * N);
  vector<bool> left(2 * N);

  auto Dfs = [&](auto dfs, int x) -> bool {
    for (int y : g[x]) {
      if (vis[y]) continue;
      vis[y] = true;
      if (match[y] == -1 || dfs(dfs, match[y])) {
        match[y] = x;
        return true;
      }
    }
    return false;
  };

  for (int i = 0; i < N; ++i) {
    if ((x1[i] + y1[i]) & 1) {
      left[2 * i] = true;
      fill(vis.begin(), vis.end(), false);
      if (!Dfs(Dfs, 2 * i)) {
        cout << "impossible\n";
        return 0;
      }
    } else {
      left[2 * i + 1] = true;
      fill(vis.begin(), vis.end(), false);
      if (!Dfs(Dfs, 2 * i + 1)) {
        cout << "impossible\n";
        return 0;
      }
    }
  }
  vector<int> color(2 * N, -1);
  for (int i = 0, p = 0; i < 2 * N; ++i) {
    if (!left[i]) {
      color[i] = p;
      color[match[i]] = p;
      p++;
    }
  }
  for (int i = 0; i < N; ++i) {
    cout << color[2 * i] << " " << color[i * 2 + 1] << "\n";
  }
}
