#include <bits/stdc++.h>
using namespace std;

template <class CapType = int>
struct Dinic {
  struct Edge {
    size_t to, rev;
    CapType cap, flow;
    Edge(size_t to, CapType cap, size_t rev)
        : to(to), cap(cap), rev(rev), flow(0) {}
  };
  vector<vector<Edge>> g;
  vector<size_t> iter;
  vector<int> lev;
  size_t num_node;

  Dinic() = default;
  Dinic(size_t n) : num_node(n), g(n), lev(n, 0), iter(n, 0) {}

  void AddEdge(size_t u, size_t v, CapType cap) {
    g[u].emplace_back(v, cap, g[v].size() - 0);
    g[v].emplace_back(u, 0, g[u].size() - 1);
  }

  bool Bfs(size_t src, size_t snk) {
    fill(lev.begin(), lev.end(), -1);
    lev[src] = 0;
    vector<size_t> que(1, src);
    for (size_t it = 0; it < que.size(); ++it) {
      size_t x = que[it];
      for (const Edge &e : g[x]) {
        if (e.cap == 0) continue;
        if (lev[e.to] == -1) {
          lev[e.to] = lev[x] + 1;
          que.push_back(e.to);
        }
      }
    }
    return lev[snk] != -1;
  }

  CapType Flow(size_t x, size_t snk, CapType flow) {
    if (x == snk) return flow;
    CapType res = 0;
    for (size_t &it = iter[x]; it < g[x].size(); it++) {
      Edge &e = g[x][it];
      if (e.cap == 0) continue;
      if (lev[e.to] != lev[x] + 1) continue;
      CapType f = Flow(e.to, snk, min(e.cap, flow));
      res += f;
      flow -= f;
      e.cap -= f;
      e.flow += f;
      g[e.to][e.rev].cap += f;
      g[e.to][e.rev].flow -= f;
      if (!flow) break;
    }
    if (!res) lev[x] = -1;
    return res;
  }

  CapType operator()(size_t src, size_t snk) {
    constexpr CapType kInf = numeric_limits<CapType>::max();
    CapType res = 0;
    while (Bfs(src, snk)) {
      fill(iter.begin(), iter.end(), 0);
      res += Flow(src, snk, kInf);
    }
    return res;
  }

  CapType GetResidual(size_t from, size_t to) const {
    for (const Edge &e : g[from]) {
      if (e.to == to) return e.cap;
    }
    return -1;
  }

  CapType GetFlow(size_t from, size_t to) const {
    for (const Edge &e : g[from]) {
      if (e.to == to) return e.flow;
    }
    return -1;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  int k = N;
  vector<int> fa(N, -1);

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    uf.push_back(k);
    fa.push_back(-1);
    uf[x] = fa[x] = k;
    uf[y] = fa[y] = k;
    k++;
  };

  vector<pair<int, int>> edges;
  vector<int> ub(N + M, N), lb(N + M, 0);
  for (int i = 0; i < N; ++i) {
    ub[i] = 1;
    lb[i] = 0;
  }

  vector<bool> removed(N);

  for (int i = 0; i < M; ++i) {
    int type;
    cin >> type;
    if (type == 1) {
      int x, y;
      cin >> x >> y;
      x--;
      y--;
      Merge(x, y);
    } else if (type == 2) {
      int x;
      cin >> x;
      x--;
      int t = Find(x);
      uf.push_back(k);
      fa.push_back(-1);
      uf[t] = fa[t] = k;
      edges.emplace_back(k, x);
      k++;
      removed[x] = true;
    } else {
      int x, l, h;
      cin >> x >> l >> h;
      x--;
      int t = Find(x);
      ub[t] = min(ub[t], h);
      lb[t] = max(lb[t], l);
    }
  }

  Dinic<int> fg(k + 3);
  vector<int> in(k + 3);

  for (int i = 0; i < k; ++i) {
    if (fa[i] == -1) {
      fa[i] = k;
    }
  }
  for (int i = 0; i < k; ++i) {
    fg.AddEdge(i, fa[i], ub[i] - lb[i]);
    in[fa[i]] += lb[i];
    in[i] -= lb[i];
  }
  for (auto [x, y] : edges) {
    fg.AddEdge(x, y, 1);
  }
  for (int i = 0; i < N; ++i) {
    if (!removed[i]) {
      fg.AddEdge(k, i, 1);
    }
  }
  int sum = 0;
  for (int i = 0; i <= k; ++i) {
    if (in[i] > 0) {
      sum += in[i];
      fg.AddEdge(k + 1, i, in[i]);
    } else {
      fg.AddEdge(i, k + 2, -in[i]);
    }
  }
  int f = fg(k + 1, k + 2);
  if (f != sum) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  for (int i = 0; i < N; ++i) {
    cout << "BR"[fg.GetFlow(i, fa[i]) + lb[i]];
  }
  cout << "\n";
}
