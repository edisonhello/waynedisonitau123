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
    for (;; swap(x, y)) {
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
  TwoSat(int N) : N(N), g(2 * N + 1), r(2 * N + 1) {}

  void AddEdge(int x, int y) {
    cout << "AddEdge x = " << x << " y = " << y << endl;
    g[x].push_back(y);
    r[y].push_back(x);
  }

  void Must(int x) {  
    cout << "Must x = " << x << endl;
    AddEdge(2 * N, x);
  }

  bool Solve(vector<bool>& sol) {
    vector<bool> vis(2 * N + 1);
    vector<int> order;

    auto Dfs = [&](auto dfs, int x) -> void {
      vis[x] = true;
      for (int u : g[x]) {
        if (!vis[u]) dfs(dfs, u);
      }
      order.push_back(x);
    };

    for (int i = 0; i < 2 * N + 1; ++i) {
      if (!vis[i]) Dfs(Dfs, i);
    }

    vector<int> scc(2 * N + 1, -1);
    int cnt = 0;

    auto RevDfs = [&](auto dfs, int x, int p) -> void {
      scc[x] = p;
      for (int u : r[x]) {
        if (scc[u] == -1) dfs(dfs, u, p);
      }
    };

    for (int i = order.size() - 1; i >= 0; --i) {
      if (scc[order[i]] == -1) {
        RevDfs(RevDfs, order[i], cnt++);
      }
    }

    for (int i = 0; i < N; ++i) {
      if (scc[i] == scc[i + N]) return false;
    }

    vector<bool> used(cnt);
    vector<bool> choose(cnt);

    vector<int> what(2 * N, -1);
    
    bool bad = false;

    auto DfsSol = [&](auto dfs, int x, int c) -> void {
      if (x < 2 * N) {
        what[x] = c;
        int y = x >= N ? x - N : x + N;
        if (what[y] != -1 && what[y] != c ^ 1) {
          bad = true;
          return;
        }
        if (what[y] == -1) dfs(dfs, y, c ^ 1);
      }
      if (c == 1) {
        for (int u : g[x]) {
          assert(u < 2 * N);
          if (what[u] != -1 && what[u] != c) {
            bad = true;
            return;
          }
          if (what[u] == -1) dfs(dfs, u, c);
        }
      }
    };

    DfsSol(DfsSol, 2 * N, 1);

    if (bad) return false;

    for (int i = 0; i < N; ++i) {
      if (what[i] != -1) {
        assert(what[i + N] != -1 && what[i + N] != what[i]);
        used[scc[i]] = true;
        used[scc[i + N]] = true;
        if (what[i] == 1) {
          choose[scc[i]] = true;
          choose[scc[i + N]] = false;
        } else {
          choose[scc[i]] = false;
          choose[scc[i + N]] = true;
        }
      }
    }

    for (int u : order) {
      if (!used[scc[u]]) {
        int v = u < N ? u + N : u - N;
        used[scc[u]] = true;
        used[scc[v]] = true;
        choose[scc[u]] = true;
        choose[scc[v]] = false;
      }
    }
    for (int i = 0; i < N; ++i) {
      if (choose[scc[i]]) sol[i] = false;
      else sol[i] = true;
    }
    return true;
  }

  vector<vector<int>> g, r;
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
  cout << "matching = " << endl;
  for (int i = 0; i < M; ++i) {
    cout << matching[i].first << " " << matching[i].second << endl;
  }
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
        int x = matching[j].first, y = matching[j].second;
        if (adj[a][x]) {
          solver.AddEdge(i + M, j);
          solver.AddEdge(j + M, i);
        }
        if (adj[a][y]) {
          solver.AddEdge(i + M, j + M);
          solver.AddEdge(j, i);
        }
        if (adj[b][x]) {
          solver.AddEdge(i, j);
          solver.AddEdge(j + M, i + M);
        }
        if (adj[b][y]) {
          solver.AddEdge(i, j + M);
          solver.AddEdge(j, i + M);
        }
      }
    }
    vector<bool> sol(M);
    if (solver.Solve(sol)) {
      cout << M << "\n";
      for (int i = 0; i < M; ++i) {
        if (sol[i])
          cout << matching[i].second + 1 << " ";
        else
          cout << matching[i].first + 1 << " ";
      }
      cout << "\n";
      return;
    }
  }
  for (int x = 0; x < N; ++x) {
    if (match[x] != -1) continue;
    cout << "C = M + 1 x = " << x << endl;
    for (int u : g[x]) {
      assert(match[u] != -1);
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
        int x = matching[j].first, y = matching[j].second;
        if (adj[a][x]) {
          solver.AddEdge(i + M, j);
          solver.AddEdge(j + M, i);
        }
        if (adj[a][y]) {
          solver.AddEdge(i + M, j + M);
          solver.AddEdge(j, i);
        }
        if (adj[b][x]) {
          solver.AddEdge(i, j);
          solver.AddEdge(j + M, i + M);
        }
        if (adj[b][y]) {
          solver.AddEdge(i, j + M);
          solver.AddEdge(j, i + M);
        }
      }
    }
    vector<bool> sol(M);
    if (solver.Solve(sol)) {
      cout << M + 1 << "\n";
      cout << x + 1 << " ";
      for (int i = 0; i < M; ++i) {
        if (sol[i])
          cout << matching[i].second + 1 << " ";
        else
          cout << matching[i].first + 1 << " ";
      }
      cout << "\n";
      return;
    }
    for (int u : g[x]) {
      adj[u][x] = true;
      adj[x][u] = true;
    }
  }
  for (int e = 0; e < M; ++e) {
    TwoSat solver(M - 1);
    vector<pair<int, int>> new_matching;
    for (int i = 0; i < M; ++i) {
      if (i != e) new_matching.push_back(matching[i]);
    }
    for (int u : g[matching[e].first]) {
      adj[u][matching[e].first] = false;
      adj[matching[e].first][u] = false;
    }
    for (int u : g[matching[e].second]) {
      adj[u][matching[e].second] = false;
      adj[matching[e].second][u] = false;
    }
    for (int i = 0; i < M - 1; ++i) {
      int a = new_matching[i].first, b = new_matching[i].second;
      for (int u : g[a]) {
        if (match[u] == -1) {
          if (adj[u][a]) solver.Must(i);
        }
      }
      for (int u : g[b]) {
        if (match[u] == -1) {
          if (adj[u][b]) solver.Must(i + M - 1);
        }
      }
    }
    for (int i = 0; i < M - 1; ++i) {
      for (int j = i + 1; j < M - 1; ++j) {
        int a = new_matching[i].first, b = new_matching[i].second;
        int x = new_matching[j].first, y = new_matching[j].second;
        if (adj[a][x]) {
          solver.AddEdge(i + M - 1, j);
          solver.AddEdge(j + M - 1, i);
        }
        if (adj[a][y]) {
          solver.AddEdge(i + M - 1, j + M - 1);
          solver.AddEdge(j, i);
        }
        if (adj[b][x]) {
          solver.AddEdge(i, j);
          solver.AddEdge(j + M - 1, i + M - 1);
        }
        if (adj[b][y]) {
          solver.AddEdge(i, j + M - 1);
          solver.AddEdge(j, i + M - 1);
        }
      }
    }
    vector<bool> sol(M - 1);
    if (solver.Solve(sol)) {
      cout << M + 1 << "\n";
      cout << matching[e].first + 1 << " " << matching[e].second + 1 << " ";
      for (int i = 0; i < M - 1; ++i) {
        if (sol[i])
          cout << new_matching[i].second + 1 << " ";
        else
          cout << new_matching[i].first + 1 << " ";
      }
      cout << "\n";
      return;
    }
    for (int u : g[matching[e].first]) {
      adj[u][matching[e].first] = true;
      adj[matching[e].first][u] = true;
    }
    for (int u : g[matching[e].second]) {
      adj[u][matching[e].second] = true;
      adj[matching[e].second][u] = true;
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
