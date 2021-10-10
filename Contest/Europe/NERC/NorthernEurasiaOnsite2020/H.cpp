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
  int n; cin >> n;
  vector<pair<int, int>> segs;
  vector<int> nums;
  for (int i = 0; i < n; ++i) {
    cin >> segs[i].first >> segs[i].second;
    nums.push_back(segs[i].first);
    nums.push_back(segs[i].second);
  }
  sort(nums.begin(), nums.end());

  vector<vector<Edge>> g(nums.size() + n * 2);

}
