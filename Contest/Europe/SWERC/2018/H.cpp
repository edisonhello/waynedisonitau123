#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  auto Dijkstra = [&](int s) {
    constexpr int kInf = 1'000'000'000;
    vector<int> dist(n, kInf);
    dist[s] = 0;
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, s);
    vector<bool> vis(n);
    while (!pq.empty()) {
      int x = pq.top().second;
      pq.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (auto e : g[x]) {
        if (dist[e.first] > dist[x] + e.second) {
          dist[e.first] = dist[x] + e.second;
          pq.emplace(-dist[e.first], e.first);
        }
      }
    }
    return dist;
  };

  vector<vector<int>> dist(3);
  for (int i = 0; i < 3; ++i) {
    dist[i] = Dijkstra(i);
  }
  vector<tuple<int, int, int>> pp;

  auto Solve = [&](int a, int b, int c) {
    vector<tuple<int, int, int>> p(n);
    vector<int> dy, dz;
    for (int i = 0; i < n; ++i) {
      p[i] = make_tuple(dist[a][i], dist[b][i], dist[c][i]); 
      dy.push_back(dist[b][i]);
      dz.push_back(dist[c][i]);
    }
    sort(dy.begin(), dy.end());
    dy.resize(unique(dy.begin(), dy.end()) - dy.begin());
    sort(dz.begin(), dz.end());
    dz.resize(unique(dz.begin(), dz.end()) - dz.begin());
    for (int i = 0; i < n; ++i) {
      get<1>(p[i]) = lower_bound(dy.begin(), dy.end(), get<1>(p[i])) - dy.begin();
      get<2>(p[i]) = lower_bound(dz.begin(), dz.end(), get<2>(p[i])) - dz.begin();
    }
    vector<bool> bad(n);
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&](int i, int j) { return get<0>(p[i]) < get<0>(p[j]); });

    auto DivideConquer = [&](auto self, vector<int> v, int l, int r) {
      if (r - l == 1) {
        int pf = dy.size();
        for (int i = 0, j = 0; i < v.size(); i = j) {
          vector<int> add, que;
          while (j < v.size() && get<0>(p[v[i]]) == get<0>(p[v[j]])) {
            pf = min(pf, get<1>(p[v[j]]));
            que.push_back(v[j]);
            j++;
          }
          for (int u : que) {
            if (pf < get<1>(p[u])) bad[u] = true;
          }
        }
        return;
      }
      int m = (l + r) >> 1;
      int pf = dy.size();
      for (int i = 0, j = 0; i < v.size(); i = j) {
        vector<int> add, que;
        while (j < v.size() && get<0>(p[v[i]]) == get<0>(p[v[j]])) {
          if (get<2>(p[v[j]]) < m) add.push_back(v[j]);
          else que.push_back(v[j]);
          j++;
        }
        for (int u : add) pf = min(pf, get<1>(p[u]));
        for (int u : que) {
          if (pf < get<1>(p[u])) bad[u] = true;
        }
      }
      vector<int> lv, rv;
      for (int i = 0; i < v.size(); ++i) {
        if (get<2>(p[v[i]]) < m) lv.push_back(v[i]);
        else rv.push_back(v[i]);
      }
      self(self, lv, l, m);
      self(self, rv, m, r);
    };
    DivideConquer(DivideConquer, v, 0, dz.size());
    return bad;
  };

  auto a = Solve(0, 1, 2);
  auto b = Solve(1, 0, 2);
  auto c = Solve(0, 2, 1);
  int res = 0;
  for (int i = 0; i < n; ++i) {
    if (!a[i] && !b[i] && !c[i]) res++;
  }
  cout << res << "\n";
  return 0;
}
