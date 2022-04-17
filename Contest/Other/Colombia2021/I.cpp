#include <bits/stdc++.h>
using namespace std;

int64_t Matching(vector<vector<int>> w) {
  int N = w.size();
  vector<int> fl(N, -1), fr(N, -1), hr(N), hl(N);
  for (int i = 0; i < N; ++i) {
    hl[i] = *max_element(w[i].begin(), w[i].end());
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
      while (x != -1) {
        swap(x, fr[fl[x] = pre[x]]);
      }
      return false;
    };

    while (true) {
      while (!que.empty()) {
        int y = que.front();
        que.pop();
        for (int x = 0, d = 0; x < N; ++x) {
          if (!vl[x] && slk[x] >= (d = hl[x] + hr[y] - w[x][y])) {
            if (pre[x] = y, d) {
              slk[x] = d;
            } else if (!Check(x)) {
              return;
            }
          }
        }
      }
      int d = kInf;
      for (int x = 0; x < N; ++x) {
        if (!vl[x] && d > slk[x]) {
          d = slk[x];
        }
      }
      for (int x = 0; x < N; ++x) {
        if (vl[x]) {
          hl[x] += d;
        } else {
          slk[x] -= d;
        }
        if (vr[x]) {
          hr[x] -= d;
        }
      }
      for (int x = 0; x < N; ++x) {
        if (!vl[x] && !slk[x] && !Check(x)) {
          return;
        }
      }
    }
  };

  for (int i = 0; i < N; ++i) {
    Bfs(i);
  }
  int64_t res = 0;
  for (int i = 0; i < N; ++i) {
    res += w[i][fl[i]];
  }
  return res;
}

int main() {
  int N, M;
  cin >> N >> M;
  constexpr int kInf = 1'000'000'000;
  vector<vector<int>> w(2 * N, vector<int>(2 * N, kInf));
  vector<int> best1(N, kInf);
  vector<int> best2(N, kInf);
  for (int i = 0; i < M; ++i) {
    int u, v, k;
    cin >> u >> v >> k;
    w[u][v] = min(w[u][v], k);
    best1[u] = min(best1[u], k);
    best2[v] = min(best2[v], k);
  }
  for (int i = 0; i < N; ++i) {
    if (best1[i] == kInf || best2[i] == kInf) {
      cout << "Impossible\n";
      return 0;
    }
  }
  for (int i = 0; i < N; ++i) {
    w[i][i + N] = best1[i];
    w[i + N][i] = best2[i];
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      w[i + N][j + N] = 0;
    }
  }
  for (int i = 0; i < 2 * N; ++i) {
    for (int j = 0; j < 2 * N; ++j) {
      w[i][j] = -w[i][j];
    }
  }
  cout << -Matching(w) << "\n";
}

