#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int kInf = 0x3f3f3f3f'3f3f3f3f;

struct Edge {
  int to, cap, rev, w;
  Edge(int t, int c, int r, int w) : to(t), cap(c), rev(r), w(w) {}
};

pair<int, int> Flow(vector<vector<Edge>> g, int s, int t) {
  int N = g.size();
  vector<int> dist(N), ed(N), pv(N);
  vector<bool> inque(N);
  int flow = 0, cost = 0;
  while (true) {
    dist.assign(N, kInf);
    inque.assign(N, false);
    pv.assign(N, -1);
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      inque[x] =false;
      for (int i = 0; i < g[x].size(); ++i) {
        Edge &e = g[x][i];
        if (e.cap > 0 && dist[e.to] > dist[x] + e.w) {
          dist[e.to] = dist[x] + e.w;
          pv[e.to] = x;
          ed[e.to] = i;
          if (!inque[e.to]) {
            inque[e.to] = true;
            que.push(e.to);
          }
        }
      }
    }

    if (dist[t] == kInf) break;
    int f = kInf;
    for (int x = t; x != s; x = pv[x])
      f = min(f, g[pv[x]][ed[x]].cap);
    for (int x = t; x != s; x = pv[x]) {
      Edge &e = g[pv[x]][ed[x]];
      e.cap -= f;
      g[e.to][e.rev].cap += f;
    }
    flow += f;
    cost += f * dist[t];
  }
  return make_pair(flow, cost);
}

int32_t main() {
  int n, k;
  cin >> n >> k;
  vector<tuple<int, int, int>> blk;
  vector<int> xs;
  for (int i = 0; i < n; ++i) {
    int l, r, x; cin >> l >> r >> x;
    blk.emplace_back(l, r, x);
    xs.push_back(l);
    xs.push_back(r);
  }

  sort(xs.begin(), xs.end());
  xs.resize(unique(xs.begin(), xs.end()) - xs.begin());

  int nn = xs.size();
  vector<vector<Edge>> g(nn + 2);

  auto AddEdge = [&](int u, int v, int f, int w) {
    g[u].emplace_back(v, f, g[v].size() - 0, w);
    g[v].emplace_back(u, 0, g[u].size() - 1, -w);
  };

  AddEdge(nn, 0, k, 0);
  AddEdge(nn - 1, nn + 1, k, 0);
  for (int i = 1; i < nn; ++i) AddEdge(i - 1, i, k, 0);

  for (auto [l, r, x] : blk) {
    l = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
    r = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
    int nr = r == nn - 1 ? nn + 1 : r + 1;
    AddEdge(l, nr, 1, -x);
  }

  auto [f, c] = Flow(g, nn, nn + 1);
  assert(f == k);
  cout << -c << endl;
}

