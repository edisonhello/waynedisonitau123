#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to, cap, rev;

  Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

int Flow(vector<vector<Edge>>& g, int s, int t) {
  int N = g.size();
  vector<int> dist(N);
  int flow = 0;
  while (true) {
    fill(dist.begin(), dist.end(), -1);
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      for (Edge& e : g[x]) {
        if (e.cap > 0 && dist[e.to] == -1) {
          dist[e.to] = dist[x] + 1;
          que.push(e.to);
        }
      }
    }
    if (dist[t] == -1) {
      break;
    }

    auto Dfs = [&](auto self, int x, int f = 1'000'000'000) -> int {
      if (x == t) {
        return f;
      }
      int res = 0;
      for (Edge& e : g[x]) {
        if (e.cap > 0 && dist[e.to] == dist[x] + 1) {
          int p = self(self, e.to, min(f - res, e.cap));
          res += p;
          e.cap -= p;
          g[e.to][e.rev].cap += p;
        }
      }
      if (res == 0) {
        dist[x] = -1;
      }
      return res;
    };

    flow += Dfs(Dfs, s);
  }
  return flow;
}

vector<int> DomTree(vector<vector<int>> g, int s) {
  int N = g.size();
  vector<vector<int>> rdom(N), r(N);
  vector<int> dfn(N, -1), rev(N, -1), fa(N, -1), sdom(N, -1), dom(N, -1),
      val(N, -1), rp(N, -1);
  int stamp = 0;

  auto Dfs = [&](auto self, int x) -> void {
    rev[dfn[x] = stamp] = x;
    fa[stamp] = sdom[stamp] = val[stamp] = stamp;
    stamp++;
    for (int u : g[x]) {
      if (dfn[u] == -1) {
        self(self, u);
        rp[dfn[u]] = dfn[x];
      }
      r[dfn[u]].push_back(dfn[x]);
    }
  };

  auto Find = [&](auto self, int x, bool c) -> int {
    if (fa[x] == x) {
      return c ? -1 : x;
    }
    int p = self(self, fa[x], true);
    if (p == -1) {
      return c ? fa[x] : val[x];
    }
    if (sdom[val[x]] > sdom[val[fa[x]]]) {
      val[x] = val[fa[x]];
    }
    fa[x] = p;
    return c ? p : val[x];
  };

  auto Merge = [&](int x, int y) { fa[x] = y; };

  Dfs(Dfs, s);

  for (int i = stamp - 1; i >= 0; --i) {
    for (int u : r[i]) {
      sdom[i] = min(sdom[i], sdom[Find(Find, u, false)]);
    }
    if (i > 0) {
      rdom[sdom[i]].push_back(i);
    }
    for (int u : rdom[i]) {
      int p = Find(Find, u, false);
      if (sdom[p] == i) {
        dom[u] = i;
      } else {
        dom[u] = p;
      }
    }
    if (i > 0) {
      Merge(i, rp[i]);
    }
  }
  vector<int> res(N, -2);
  res[s] = -1;
  for (int i = 0; i < stamp; ++i) {
    if (sdom[i] != dom[i]) {
      dom[i] = dom[dom[i]];
    }
  }
  for (int i = 1; i < stamp; ++i) {
    res[rev[i]] = rev[dom[i]];
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<int> color(N, -1);
  for (int i = 0; i < N; ++i) {
    if (color[i] == -1) {
      vector<int> que = {i};
      color[i] = 0;
      for (int it = 0; it < que.size(); ++it) {
        int x = que[it];
        for (int u : g[x]) {
          if (color[u] == -1) {
            color[u] = 1 - color[x];
            que.push_back(u);
          }
        }
      }
    }
  }

  vector<vector<Edge>> fg(N + 2);

  auto AddEdge = [&](int from, int to, int cap) {
    fg[from].emplace_back(to, cap, fg[to].size());
    fg[to].emplace_back(from, 0, fg[from].size() - 1);
  };

  for (int i = 0; i < N; ++i) {
    if (color[i] == 0) {
      AddEdge(N, i, 1);
      for (int u : g[i]) {
        assert(color[u] == 1);
        AddEdge(i, u, 1);
      }
    } else {
      AddEdge(i, N + 1, 1);
    }
  }
  int f = Flow(fg, N, N + 1);
  vector<int> match(N, -1);
  for (int i = 0; i < N; ++i) {
    if (color[i] == 0) {
      for (Edge& e : fg[i]) {
        if (e.to < N && color[e.to] == 1 && e.cap == 0) {
          match[i] = e.to;
          match[e.to] = i;
          // cerr << "match " << i << " " << e.to << endl;
        }
      }
    }
  }
  int64_t ans = 0;
  int unmatched = count(match.begin(), match.end(), -1);
  ans += 1LL * unmatched * (unmatched - 1) / 2;

  int cnt[2] = {0, 0};

  for (int c = 0; c < 2; ++c) {
    vector<vector<int>> dg(N + 1);
    for (int i = 0; i < N; ++i) {
      if (color[i] == c) {
        for (int u : g[i]) {
          if (match[i] == u) {
            dg[i].push_back(u);
          } else {
            dg[u].push_back(i);
          }
        }
      }
    }
    for (int i = 0; i < N; ++i) {
      if (color[i] == 1 - c && match[i] == -1) {
        dg[N].push_back(i);
      }
    }
    vector<int> dom = DomTree(dg, N);
    vector<vector<int>> tree(N + 1);
    for (int i = 0; i < N + 1; ++i) {
      if (dom[i] >= 0) {
        tree[dom[i]].push_back(i);
      }
    }

    vector<int> block(N + 1);
    vector<int> sz(N + 1);

    auto Dfs = [&](auto self, int x, int b = 0) -> void {
      if (x < N && color[x] == 1 - c && match[x] == -1) {
        b++;
      }
      block[x] = b;
      if (x < N && color[x] == c && match[x] != -1) {
        sz[x] = 1;
      }
      for (int u : tree[x]) {
        self(self, u, b);
        sz[x] += sz[u];
      }
    };

    Dfs(Dfs, N);

    for (int i = 0; i < N; ++i) {
      if (color[i] == c && match[i] != -1 && dom[i] >= 0) {
        ans += unmatched - block[i];
      }
    }

    int cur = 0;
    for (int i = 0; i < N; ++i) {
      if (dom[i] == N) {
        ans += 1LL * cur * sz[i];
        cur += sz[i];
      }
    }

    for (int i = 0; i < N; ++i) {
      if (color[i] == c && dom[i] >= 0) {
        cnt[c]++;
      }
    }
  }

  ans += 1LL * cnt[0] * cnt[1];

  cout << ans << "\n";
  return 0;
}
