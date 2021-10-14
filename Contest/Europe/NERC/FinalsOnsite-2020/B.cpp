#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to, cap, rev, w;
  Edge(int a, int b, int c, int d) : to(a), cap(b), rev(c), w(d) {}
};

pair<int, int> CostFlow(vector<vector<Edge>>& g, int s, int t) {
  int N = g.size();
  constexpr int kInf = 1'000'000'000;
  vector<int> dist(N, kInf), p(N, -1), ed(N, -1);
  vector<bool> inque(N);
  int cost = 0;
  int flow = 0;
  while (true) {
    fill(dist.begin(), dist.end(), kInf);
    fill(inque.begin(), inque.end(), false);
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      inque[x] = false;
      for (int i = 0; i < g[x].size(); ++i) {
        const Edge& e = g[x][i];
        if (e.cap > 0) {
          if (dist[e.to] > dist[x] + e.w) {
            dist[e.to] = dist[x] + e.w;
            p[e.to] = x;
            ed[e.to] = i;
            if (!inque[e.to]) {
              inque[e.to] = true;
              que.push(e.to);
            }
          }
        }
      }
    }
    if (dist[t] == kInf) break;
    int f = kInf;
    for (int x = t; x != s; x = p[x]) {
      f = min(f, g[p[x]][ed[x]].cap);
    }
    for (int x = t; x != s; x = p[x]) {
      Edge& e = g[p[x]][ed[x]];
      e.cap -= f;
      g[e.to][e.rev].cap += f;
    }
    cost += f * dist[t];
    flow += f;
  }
  return make_pair(flow, cost);
}

int main() {
  int D, N;
  cin >> D >> N;
  vector<int> mask(N);
  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < D; ++j) {
      if (s[j] == '1') mask[i] ^= (1 << j);
    }
  }

  vector<vector<Edge>> g(2 * N + 2);

  auto AddEdge = [&](int a, int b, int c, int d) {
    g[a].emplace_back(b, c, g[b].size(), d);
    g[b].emplace_back(a, 0, g[a].size() - 1, -d);
  };

  for (int i = 0; i < N; ++i) {
    AddEdge(N + N, i, 1, 0);
    AddEdge(i + N, N + N + 1, 1, 0);
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i == j) continue;
      if ((mask[i] & mask[j]) == mask[i]) {
        AddEdge(i, j + N, 1, -__builtin_popcount(mask[i]));
      }
    }
  }
  pair<int, int> res = CostFlow(g, N + N, N + N + 1);
  vector<int> to(N, -1);
  for (int i = 0; i < N; ++i) {
    for (Edge& e : g[i]) {
      if (e.to >= N && e.to < N + N && e.cap == 0) {
        assert(to[i] == -1);
        to[i] = e.to - N;
      }
    }
  }
  vector<bool> used(N);
  vector<int> ans;
  bool f = true;
  while (true) {
    int y = -1;
    for (int i = 0; i < N; ++i) {
      if (used[i]) continue;
      if (y == -1 || __builtin_popcount(mask[i]) < __builtin_popcount(mask[y])) {
        y = i;
      }
    }
    if (y == -1) break;
    used[y] = true;
    if (!f) {
      ans.push_back(-1);
    }
    f = false;
    for (int i = 0; i < D; ++i) {
      if (mask[y] >> i & 1) ans.push_back(i);
    }
    while (to[y] != -1) {
      int x = to[y];
      used[x] = true;
      assert((mask[x] & mask[y]) == mask[y]);
      int diff = mask[x] ^ mask[y];
      for (int i = 0; i < D; ++i) {
        if (diff >> i & 1) ans.push_back(i);
      }
      y = to[y];
    }
  }
  cout << ans.size() << "\n";
  for (int u : ans) {
    if (u == -1) cout << "R";
    else cout << u;
    cout << " ";
  }
  cout << "\n";
}
