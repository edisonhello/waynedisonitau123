#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to, cap, rev;

  Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

int MaxFlow(vector<vector<Edge>>& g, int s, int t) {
  int N = g.size();
  vector<int> level(N, -1);
  int res = 0;
  while (true) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      for (Edge& e : g[x]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[x] + 1;
          que.push(e.to);
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
          int p = dfs(dfs, e.to, min(f - res, e.cap));
          res += p;
          e.cap -= p;
          g[e.to][e.rev].cap += p;
        }
      }
      if (res == 0) level[x] = -1;
      return res;
    };

    res += Dfs(Dfs, s);
  }
  return res;
}

int main() {
  int N, M;
  cin >> N >> M;

  vector<vector<Edge>> g(N + N + 2);
  vector<vector<int>> lg(N), rg(N);

  auto AddEdge = [&](int from, int to, int cap) {
    g[from].emplace_back(to, cap, g[to].size());
    g[to].emplace_back(from, cap, g[from].size() - 1);
  };

  vector<pair<int, int>> edges;
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    lg[u].push_back(v);
    rg[v].push_back(u);
    AddEdge(u, v + N, 1);
  }
  for (int i = 0; i < N; ++i) {
    AddEdge(N + N, i, 1);
    AddEdge(i + N, N + N + 1, 1);
  }

  int f = MaxFlow(g, N + N, N + N + 1);
  vector<int> lm(N, -1), rm(N, -1);
  for (int i = 0; i < N; ++i) {
    for (Edge& e : g[i]) {
      if (e.to >= N && e.to < N + N && e.cap == 0) {
        lg[i].push_back(e.to - N);
        rg[e.to - N].push_back(i);
        lm[i] = e.to - N;
        rm[e.to - N] = i;
      }
    }
  }
  queue<int> que;
  vector<bool> vis(N);
  vector<int> ans;
  for (int i = 0; i < N; ++i) {
    if (lm[i] == -1) {
      ans.push_back(i);
      que.push(i);
      vis[i] = true;
    }
  }
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int u : lg[x]) {
      if (rm[u] != -1) {
        // ans.push_back(u);
        if (!vis[rm[u]]) {
          vis[rm[u]] = true;
          que.push(rm[u]);
          ans.push_back(rm[u]);
        }
      }
    }
  }
  fill(vis.begin(), vis.end(), false);
  for (int i = 0; i < N; ++i) {
    if (rm[i] == -1) {
      que.push(i);
      ans.push_back(i);
      vis[i] = true;
    }
  }
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int u : rg[x]) {
      if (lm[u] != -1) {
        // ans.push_back(u);
        if (!vis[lm[u]]) {
          vis[lm[u]] = true;
          que.push(lm[u]);
          ans.push_back(lm[u]);
        }
      }
    }
  }
  sort(ans.begin(), ans.end());
  ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
  cout << N - f - 1 << "\n";
  if (N - f - 1 > 0) {
    for (int u : ans) cout << u + 1 << " ";
  }
  cout << "\n";
}

