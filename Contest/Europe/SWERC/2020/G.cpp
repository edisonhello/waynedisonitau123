#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K;
  cin >> N >> K;
  vector<int> dv(N + 1);
  for (int i = 1; i <= N; ++i) {
    for (int j = i; j <= N; j += i) {
      dv[j]++;
    }
  }
  vector<vector<int>> g(N);
  vector<int> deg(N);
  vector<int> to(N, -1);
  for (int i = 0; i < N; ++i) {
    int j = (i + dv[i]) % N;
    g[i].push_back(j);
    g[j].push_back(i);
    to[i] = j;
    deg[i]++;
    deg[j]++;
  }
  vector<int> que;
  vector<bool> on_cycle(N, true);
  for (int i = 0; i < N; ++i) {
    if (deg[i] == 1) {
      que.push_back(i);
      on_cycle[i] = false;
    }
  }
  for (int i = 0; i < que.size(); ++i) {
    int x = que[i];
    for (int u : g[x]) {
      if (--deg[u] == 1) {
        que.push_back(u);
        on_cycle[u] = false;
      }
    }
  }
  
  vector<int64_t> sum(N);
  vector<vector<int>> up(N, vector<int>(20, -1));
  vector<int> dep(N);
  vector<int> root(N);

  auto Dfs = [&](auto dfs, int x, int r, int p = -1) -> void {
    sum[x] = (p >= 0 ? sum[p] : 0) + x;
    up[x][0] = p;
    root[x] = r;
    for (int u : g[x]) {
      if (u == p || on_cycle[u]) {
        continue;
      }
      dep[u] = dep[x] + 1;
      dfs(dfs, u, r, x);
    }
  };
  // cerr << "here" << endl;

  for (int i = 0; i < N; ++i) {
    if (on_cycle[i]) {
      Dfs(Dfs, i, i, -1);
    }
  }

  for (int d = 1; d < 20; ++d) {
    for (int i = 0; i < N; ++i) {
      if (up[i][d - 1] != -1) {
        up[i][d] = up[up[i][d - 1]][d - 1];
      }
    }
  }

  // cerr << "here" << endl;

  vector<bool> vis(N);
  vector<int> id(N, -1);
  vector<vector<int>> cycles(N);
  vector<vector<int64_t>> pres(N);
  vector<int> pos(N, -1);
  for (int i = 0; i < N; ++i) {
    if (on_cycle[i] && !vis[i]) {
      int x = i;
      vector<int> cycle;
      while (!vis[x]) {
        pos[x] = cycle.size();
        vis[x] = true;
        id[x] = i;
        cycle.push_back(x);
        x = to[x];
      }
      cycles[i] = cycle;
      cycles[i].insert(cycles[i].end(), cycle.begin(), cycle.end());
      pres[i].resize(cycles[i].size());
      for (int j = 0; j < cycles[i].size(); ++j) {
        pres[i][j] = (j > 0 ? pres[i][j - 1] : 0) + cycles[i][j];
      }
    }
  }

  auto GetUp = [&](int x, int k) {
    for (int i = 0; i < 20; ++i) {
      if (k >> i & 1) {
        x = up[x][i];
      }
    }
    return x;
  };

  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  int64_t ans = kInf;
  int best = -1;
  // cerr << "dep[1] = " << dep[1] << endl;
  for (int i = 0; i < N; ++i) {
    if (!on_cycle[i]) {
      int d = dep[i];
      if (d + 1 >= K) {
        int u = K > dep[i] ? -1 : GetUp(i, K);
        int64_t s = sum[i] - (u >= 0 ? sum[u] : 0);
        if (s < ans) {
          ans = s;
          best = i;
        }
      } else {
        int remain = K - (d + 1);
        int r = root[i];
        assert(on_cycle[r]);
        int p = id[r];
        int64_t s = sum[i];
        if (cycles[p].size() / 2 > remain) {
          s += pres[p][pos[r] + remain] - pres[p][pos[r]];
          if (s < ans) {
            ans = s;
            best = i;
          }
        }
      }
    } else {
      int p = id[i];
      if (cycles[p].size() / 2 >= K) {
        int64_t s = pres[p][pos[i] + K - 1] - (pos[i] > 0 ? pres[p][pos[i] - 1] : 0);
        if (s < ans) {
          ans = s;
          best = i;
        }
      }
    }
  }
  if (ans == kInf) {
    cout << -1 << "\n";
    return 0;
  }
  for (int i = 0; i < K; ++i) {
    cout << best << " ";
    best = to[best];
  }
  cout << "\n";
  return 0;
}
