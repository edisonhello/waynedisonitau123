#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to, cap, rev;

  Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

int Flow(vector<vector<Edge>> g, int s, int t) {
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
      if (x == t) {
        return f;
      }
      int sum = 0;
      for (Edge& e : g[x]) {
        if (e.cap > 0 && level[e.to] == level[x] + 1) {
          int p = dfs(dfs, e.to, min(e.cap, f - sum));
          e.cap -= p;
          g[e.to][e.rev].cap += p;
          sum += p;
        }
      }
      if (sum == 0) {
        level[x] = -1;
      }
      return sum;
    };

    res += Dfs(Dfs, s);
  };

  return res;
}

int main() {
  int n, m;
  cin >> n >> m;

  auto gid = [&](int i, int j) { return i * m + j; };

  vector<string> ma(n), mb(n);
  for (int i = 0; i < n; ++i) cin >> ma[i];
  for (int i = 0; i < n; ++i) cin >> mb[i];

  vector<int> djs(n * m + 1);
  iota(djs.begin(), djs.end(), 0);

  function<int(int)> F = [&](int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); };
  auto U = [&](int x, int y) {
    djs[F(x)] = F(y);
  };


  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i && ma[i][j] == ma[i - 1][j]) U(gid(i - 1, j), gid(i, j));
      if (j && ma[i][j] == ma[i][j - 1]) U(gid(i, j - 1), gid(i, j));
    }
  }

  vector<int> kpt(n * m + 1, 0);
  vector<int> ipt(n * m + 1, 0);

  int offset = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (ma[i][j] == mb[i][j]) {
        ++offset;
        ++kpt[F(gid(i, j))];
      } else {
        ++ipt[F(gid(i, j))];
      }
    }
  }

  vector<int> pt(n * m, 0);
  int ans = 0;
  for (int i = 0; i < n * m; ++i) {
    pt[i] = max(0, ipt[i] - kpt[i]);
    ans += pt[i];

    //cout << "pt = " << pt[i] << endl;
  }
  //cout << "off " << offset << endl;

  // vector<vector<int>> g(n * m);

  vector<vector<Edge>> g(n * m + 2);

  auto AddEdge = [&](int from, int to, int cap) {
    g[from].emplace_back(to, cap, g[to].size());
    g[to].emplace_back(from, 0, g[from].size() - 1);
    //cout << "from to cap " << from << ' ' << to << ' ' << cap << endl;
  };


  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i && F(gid(i, j)) != F(gid(i - 1, j))) {
        if (ma[i][j] == '1') {
          AddEdge(F(gid(i, j)), F(gid(i - 1, j)), 1'000'000'000);
        } else {
          AddEdge(F(gid(i - 1, j)), F(gid(i, j)), 1'000'000'000);
        }
      }
      if (j && F(gid(i, j)) != F(gid(i, j - 1))) {
        if (ma[i][j] == '1') {
          AddEdge(F(gid(i, j)), F(gid(i, j - 1)), 1'000'000'000);
        } else {
          AddEdge(F(gid(i, j - 1)), F(gid(i, j)), 1'000'000'000);
        }
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (F(gid(i, j)) == gid(i, j)) {
        if (ma[i][j] == '1') {
          AddEdge(n * m, gid(i, j), pt[gid(i, j)]);
        } else {
          AddEdge(gid(i, j), n * m + 1, pt[gid(i, j)]);
        }
      }
    }
  }

  
  cout << n * m - (ans - Flow(g, n * m, n * m + 1) + offset) << "\n";
  return 0;
}

