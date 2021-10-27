#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to, cap, rev;

  Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

int64_t Flow(vector<vector<Edge>> g, int s, int t) {
  int N = g.size();
  vector<int> level(N, -1);
  int64_t res = 0;
  while (true) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    vector<int> que(1, s);
    for (int it = 0; it < que.size(); ++it) {
      int x = que[it];
      for (const Edge& e : g[x]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[x] + 1;
          que.push_back(e.to);
        }
      }
    }
    if (level[t] == -1) {
      break;
    }

    auto Dfs = [&](auto dfs, int x, int f = 1'000'000'000) -> int {
      if (x == t) return f;
      int res = 0;
      for (Edge& e : g[x]) {
        if (e.cap > 0 && level[e.to] == level[x] + 1) {
          int p = dfs(dfs, e.to, min(e.cap, f - res));
          e.cap -= p;
          g[e.to][e.rev].cap += p; 
          res += p;
        }
      }
      if (res == 0) {
        level[x] = -1;
      }
      return res;
    };

    res += Dfs(Dfs, s);
  }
  return res;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> st(M), ed(M);
  for (int i = 0; i < M; ++i) {
    cin >> st[i] >> ed[i];
  }
  vector<int> V(N);
  for (int i = 0; i < N; ++i) {
    cin >> V[i];
  }
  int Q;
  cin >> Q;
  vector<tuple<int, int, int, int, int>> vec(Q);
  for (int i = 0; i < Q; ++i) {
    cin >> get<0>(vec[i]) >> get<1>(vec[i]) >> get<2>(vec[i]) >> get<3>(vec[i]) >> get<4>(vec[i]);
  }
  constexpr int kInf = 1'000'000'000;
  int ans = kInf;
  for (int s = 0; s < (1 << Q); ++s) {
    vector<vector<int>> value(N, vector<int>(16, 0));
    for (int i = 0; i < N; ++i) {
      if (V[i] != -1) {
        for (int j = 0; j < 16; ++j) {
          value[i][j] |= 1 << (V[i] >> j & 1);
        }
      }
    }
    for (int q = 0; q < Q; ++q) {
      auto [t, u, i, v, j] = vec[q];
      if (t == 0) {
        value[u][i] |= 1 << (s >> q & 1);
        value[v][j] |= 1 << (s >> q & 1);
      } else {
        value[u][i] |= 1 << (s >> q & 1);
        value[v][j] |= 1 << (1 - (s >> q & 1));
      }
    }
    bool ok = true;
    for (int i = 0; i < N; ++i) {
      for (int bit = 0; bit < 16; ++bit) {
        if (value[i][bit] == 3) {
          ok = false;
          break;
        }
      }
    }
    if (!ok) {
      continue;
    }

    int res = 0;
    for (int bit = 0; bit < 16; ++bit) {
      vector<vector<Edge>> g(N + 2);

      auto AddEdge = [&](int from, int to, int cap) {
        g[from].emplace_back(to, cap, g[to].size());
        g[to].emplace_back(from, 0, g[from].size() - 1);
      };
      for (int i = 0; i < N; ++i) {
        if (value[i][bit] == 1) {
          AddEdge(N, i, kInf);
        } else if (value[i][bit] == 2) {
          AddEdge(i, N + 1, kInf);
        }
      }
      for (int j = 0; j < M; ++j) {
        AddEdge(st[j], ed[j], 1);
        AddEdge(ed[j], st[j], 1);
      }
      int k = Flow(g, N, N + 1); 
      res += k;
    }
    ans = min(ans, res);
  }
  if (ans == kInf) ans = -1;
  cout << ans << "\n";
}
