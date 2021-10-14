#include <bits/stdc++.h>
using namespace std;

vector<int> MaxMatching(vector<vector<int>> g) {
  int N = g.size();
  vector<int> match(N + 1, N), pre(N + 1, N);
  vector<int> fa(N + 1), s(N + 1), v(N + 1);
  queue<int> que;
  
  function<int(int)> Find = [&](int u) {
    return u == fa[u] ? u : fa[u] = Find(fa[u]);
  };

  auto LCA = [&](int x, int y) {
    static int tk = 0;
    tk++;
    x = Find(x);
    y = Find(y);
    for (; ; swap(x, y)) {
      if (x != N) {
        if (v[x] == tk) return x;
        v[x] = tk;
        x = Find(pre[match[x]]);
      }
    }
  };

  auto Blossom = [&](int x, int y, int l) {
    while (Find(x) != l) {
      pre[x] = y;
      y = match[x];
      if (s[y] == 1) {
        que.push(y);
        s[y] = 0;
      }
      if (fa[x] == x) fa[x] = l;
      if (fa[y] == y) fa[y] = l;
      x = pre[y];
    }
  };

  auto Bfs = [&](int r) {
    iota(fa.begin(), fa.end(), 0);
    fill(s.begin(), s.end(), -1);
    while (!que.empty()) que.pop();
    que.push(r);
    s[r] = 0;
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      for (int u : g[x]) {
        if (s[u] == -1) {
          pre[u] = x;
          s[u] = 1;
          if (match[u] == N) {
            for (int a = u, b = x, last; b != N; a = last, b = pre[a]) {
              last = match[b];
              match[b] = a;
              match[a] = b;
            }
            return true;
          }
          que.push(match[u]);
          s[match[u]] = 0;
        } else if (!s[u] && Find(u) != Find(x)) {
          int l = LCA(u, x);
          Blossom(x, u, l);
          Blossom(u, x, l);
        }
      }
    }
    return false;
  };

  for (int x = 0; x < N; ++x) {
    if (match[x] == N) Bfs(x);
  }
  for (int x = 0; x < N; ++x) {
    if (match[x] == N) match[x] = -1;
  }
  match.resize(N);
  return match;
}

struct TwoSat {
  TwoSat(int N) : N(N), uf(2 * N), must(2 * N) {
    iota(uf.begin(), uf.end(), 0); 
  }

  int Find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  }

  void Merge(int x, int y) {
    x = Find(x);
    y = Find(y);
    uf[x] = y;
    if (must[x]) must[y] = true;
  }

  void AddEdge(int x, int y) {
    cout << "AddEdge x = " << x << " y = " << y << endl;
    Merge(x, y);
  }

  void Must(int x) {
    cout << "must x = " << x << endl;
    must[x] = true;
  }

  bool Solve(vector<bool>& sol) {
    for (int i = 0; i < N; ++i) {
      if (Find(i) == Find(i + N)) return false;
      if (must[Find(i)] && must[Find(i + N)]) return false;
    }
    vector<bool> used(N);
    for (int i = 0; i < 2 * N; ++i) {
      if (i != Find(i)) continue;
      if (must[i]) {
        for (int j = 0; j < N; ++j) {
          if (Find(j) == i) {
            used[j] = true;
            sol[j] = false;
          } else if (Find(j + N) == i) {
            used[j] = true;
            sol[j] = true;
          }
        }
      }
    }
    for (int i = 0; i < N; ++i) {
      if (used[i]) continue;
      sol[i] = false;
      used[i] = true;
      for (int j = 0; j < N; ++j) {
        if (used[j]) continue;
        if (Find(j) == Find(i)) {
          used[j] = true;
          sol[j] = false;
        } else if (Find(j + N) == Find(i)) {
          used[j] = true;
          sol[j] = true;
        }
      }
    }
    return true;
  }

  vector<int> uf;
  vector<bool> must;
  int N;
};

void Solve() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> g(N);
  vector<vector<bool>> adj(N, vector<bool>(N));
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
    adj[u][v] = true;
    adj[v][u] = true;
  }
  vector<int> match = MaxMatching(g);
  vector<bool> used(N);
  vector<pair<int, int>> matching;

  for (int i = 0; i < N; ++i) {
    if (match[i] == -1) continue;
    if (used[i]) continue;
    matching.emplace_back(i, match[i]);
    used[i] = true;
    used[match[i]] = true;
  }

  M = matching.size();
  {
    TwoSat solver(M);
    for (int i = 0; i < M; ++i) {
      int a = matching[i].first, b = matching[i].second;
      for (int u : g[a]) {
        if (match[u] == -1) {
          solver.Must(i);
        }
      }
      for (int u : g[b]) {
        if (match[u] == -1) {
          solver.Must(i + M);
        }
      }
    }
    for (int i = 0; i < M; ++i) {
      for (int j = i + 1; j < M; ++j) {
        int a = matching[i].first, b = matching[i].second;
        int x = matching[j].first, y = matching[i].second;
        if (adj[a][x]) {
          solver.AddEdge(i + M, j);
        }
        if (adj[a][y]) {
          solver.AddEdge(i + M, j + M);
        }
        if (adj[b][x]) {
          solver.AddEdge(i, j);
        }
        if (adj[b][y]) {
          solver.AddEdge(i, j + M);
        }
      }
    }
    vector<bool> sol(M);
    if (solver.Solve(sol)) {
      cout << M << "\n";
      for (int i = 0; i < M; ++i) {
        if (sol[i]) cout << matching[i].second + 1 << " ";
        else cout << matching[i].first + 1 << " ";
      }
      cout << "\n";
      return;
    }
  }
  for (int x = 0; x < N; ++x) {
    cout << "C = M + 1 x = " << x << endl;
    for (int u : g[x]) {
      adj[u][x] = false;
      adj[x][u] = false;
    }
    TwoSat solver(M);
    for (int i = 0; i < M; ++i) {
      int a = matching[i].first, b = matching[i].second;
      for (int u : g[a]) {
        if (match[u] == -1) {
          if (adj[u][a]) solver.Must(i);
        }
      }
      for (int u : g[b]) {
        if (match[u] == -1) {
          if (adj[u][b]) solver.Must(i + M);
        }
      }
    }
    for (int i = 0; i < M; ++i) {
      for (int j = i + 1; j < M; ++j) {
        int a = matching[i].first, b = matching[i].second;
        int x = matching[j].first, y = matching[i].second;
        if (adj[a][x]) {
          solver.AddEdge(i + M, j);
        }
        if (adj[a][y]) {
          solver.AddEdge(i + M, j + M);
        }
        if (adj[b][x]) {
          solver.AddEdge(i, j);
        }
        if (adj[b][y]) {
          solver.AddEdge(i, j + M);
        }
      }
    }
    vector<bool> sol(M);
    if (solver.Solve(sol)) {
      cout << M + 1 << "\n";
      cout << x + 1 << " ";
      for (int i = 0; i < M; ++i) {
        if (sol[i]) cout << matching[i].second + 1 << " ";
        else cout << matching[i].first + 1 << " ";
      }
      cout << "\n";
      return;
    }
    for (int u : g[x]) {
      adj[u][x] = true;
      adj[x][u] = true;
    }
  }
  cout << "not smol\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    Solve();
  }
}
