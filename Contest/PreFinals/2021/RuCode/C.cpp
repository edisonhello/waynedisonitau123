#include <bits/stdc++.h>
using namespace std;

pair<int64_t, vector<int>> KuhnMunkres(vector<vector<int>> W) {
  int N = W.size();
  vector<int> fl(N, -1), fr(N, -1), hr(N), hl(N);
  for (int i = 0; i < N; ++i) {
    hl[i] = *max_element(W[i].begin(), W[i].end());
  }

  constexpr int kInf = 1'000'000'000;

  auto Bfs = [&](int s) {
    vector<int> slk(N, kInf), pre(N);
    vector<bool> vl(N), vr(N);
    queue<int> que;
    que.push(s);
    vr[s] = true;
    
    auto Check = [&](int x) -> bool {
      if (vl[x] = true, fl[x] != -1) {
        que.push(fl[x]);
        return vr[fl[x]] = true;
      }
      while (x != -1) swap(x, fr[fl[x] = pre[x]]);
      return false;
    };

    while (true) {
      while (!que.empty()) {
        int y = que.front();
        que.pop();
        for (int x = 0, d = 0; x < N; ++x) {
          if (!vl[x] && slk[x] >= (d = hl[x] + hr[y] - W[x][y])) {
            if (pre[x] = y, d) slk[x] = d;
            else if (!Check(x)) return;
          }
        }
      }
      int d = kInf;
      for (int x = 0; x < N; ++x) {
        if (!vl[x] && d > slk[x]) d = slk[x];
      }
      for (int x = 0; x < N; ++x) {
        if (vl[x]) hl[x] += d;
        else slk[x] -= d;
        if (vr[x]) hr[x] -= d;
      }
      for (int x = 0; x < N; ++x) {
        if (!vl[x] && !slk[x] && !Check(x)) return;
      }
    }
  };

  for (int i = 0; i < N; ++i) Bfs(i);
  int64_t res = 0;
  for (int i = 0; i < N; ++i) res += W[i][fl[i]];
  return make_pair(res, fl);
}

int main() {
  int N, M, K;
  cin >> N >> M >> K;

  vector<int> x(N);
  for (int i = 0; i < N; ++i) cin >> x[i];
  const int T = max(N, M);
  vector<vector<int>> W(T, vector<int>(T));
  vector<vector<bool>> edge(N, vector<bool>(M));

  for (int i = 0; i < K; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    W[u][v] = x[u];
    edge[u][v] = true;
  }

  auto [cost, match] = KuhnMunkres(W);

  vector<int> dist(N + M);
  vector<int> y(N), z(M);
  queue<int> que;
  vector<bool> inque(N + M);
  for (int i = 0; i < N + M; ++i) {
    que.push(i);
    inque[i] = true;
  }
  while (!que.empty()) {
    int p = que.front();
    que.pop();
    inque[p] = false;
    if (p < N) {
      for (int i = 0; i < M; ++i) {
        if (!edge[p][i]) continue;
        if (i == match[p]) {
          if (z[i] != x[p] - y[p]) {
            z[i] = x[p] - y[p];
            if (!inque[i + N]) {
              inque[i + N] = true;
              que.push(i + N);
            }
          }
        } else {
          if (z[i] + y[p] < x[p]) {
            z[i] = x[p] - y[p];
            if (!inque[i + N]) {
              inque[i + N] = true;
              que.push(i + N);
            }
          }
        }
      }
    } else {
      for (int i = 0; i < N; ++i) {
        if (!edge[i][p]) continue;
        if (match[i] == p) {
          if (z[p] + y[i] != x[i]) {
            y[i] = x[i] - z[p];
            if (!inque[i]) {
              inque[i] = true;
              que.push(i);
            }
          }
        } else {
          if (z[p] + y[i] < x[i]) {
            y[i] = x[i] - z[p];
            if (!inque[i]) {
              inque[i] = true;
              que.push(i);
            }
          }
        }
      }
    }
  }

  // vector<vector<pair<int, int>>> g(N + M + 1);
  // for (int i = 0; i < N; ++i) {
  //   for (int j = 0; j < M; ++j) {
  //     if (!edge[i][j]) continue;
  //     g[i].emplace_back(j + N, x[i]);
  //   }
  // }
  // for (int i = 0; i < N; ++i) {
  //   for (int j = 0; j < M; ++j) {
  //     if (!edge[i][j]) continue;
  //     if (j != match[i]) continue;
  //     g[j + N].emplace_back(i, -x[i]);
  //   }
  // }
  // for (int i = 0; i < N; ++i) g[i].emplace_back(N + M, 0);
  // for (int i = 0; i < M; ++i) g[N + M].emplace_back(i + N, 0);
  // constexpr int kInf = 2'000'000'000;
  // vector<int> dist(N + M + 1);
  // for (int i = 0; i < N; ++i) dist[i] = kInf;
  // for (int i = 0; i < M; ++i) dist[i + N] = -kInf;
  // vector<bool> inque(N + M + 1);
  // dist[N + M] = 0;
  // queue<int> que;
  // que.push(N + M);
  // while (!que.empty()) {
  //   int x = que.front();
  //   que.pop();
  //   inque[x] = false;
  //   for (auto [u, w] : g[x]) {
  //     if (dist[u] > dist[x] + w) {
  //       dist[u] = dist[x] + w;
  //       if (!inque[u]) {
  //         inque[u] = true;
  //         que.push(u);
  //       }
  //     }
  //   }
  // }
  // for (int i = 0; i < N + M; ++i) if (dist[i] == kInf) dist[i] = 0;
  cout << cost << endl;
  for (int i = 0; i < N; ++i) cout << y[i] << " ";
  cout << endl;
  for (int i = 0; i < M; ++i) cout << z[i] << " ";
  cout << endl;
}
