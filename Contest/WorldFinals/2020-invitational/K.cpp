#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct MaxClique {
  vector<int> deg;
  vector<bitset<100>> adj;
  bitset<100> ans;
  int n;
  vector<pair<int, int>> edge;

  MaxClique(int n) : deg(n), n(n), adj(n) {}

  void AddEdge(int u, int v) {
    edge.emplace_back(u, v);
    ++deg[u];
    ++deg[v];
  }

  void Dfs(bitset<100> r, bitset<100> p) {
    if (clock() > 1.9 * CLOCKS_PER_SEC) {
      return;
    }
    if (p.count() == 0) {
      if (r.count() > ans.count()) {
        ans = r;
      }
      return;
    }
    if ((r | p).count() <= ans.count()) {
      return;
    }
    int x = p._Find_first();
    bitset<100> c = p & ~adj[x];
    for (int y = c._Find_first(); y < n; y = c._Find_next(y)) {
      r.set(y);
      Dfs(r, p & adj[y]);
      r.reset(y);
      p.reset(y);
    }
  }

  vector<int> operator()() {
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int u, int v) {
      return deg[u] < deg[v];
    });
    vector<int> id(n);
    for (int i = 0; i < n; ++i) {
      id[order[i]] = i;
    }
    for (auto e : edge) {
      int u = id[e.first];
      int v = id[e.second];
      adj[u].set(v);
      adj[v].set(u);
    }
    bitset<100> r{}, p{};
    for (int i = 0; i < n; ++i) {
      p.set(i);
    }
    Dfs(r, p);
    vector<int> res;
    for (int i = 0; i < n; ++i) {
      if (ans.test(i)) {
        res.push_back(order[i]);
      }
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int P, N;
  cin >> P >> N;
  vector<int> s(N);
  for (int i = 0; i < N; ++i) {
    cin >> s[i];
    s[i]--;
  }
  int K;
  cin >> K;
  vector<pair<int, int>> edge;
  vector<bool> vis(N), out(N);
  for (int i = 0; i < K; ++i) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    if (a > b) {
      swap(a, b);
    }
    edge.emplace_back(a, b);
    vis[a] = true;
    vis[b] = true;
    if (s[a] != s[b]) {
      out[a] = true;
      out[b] = true;
    }
  }

  auto Solve = [&](vector<int> vec) {
    sort(vec.begin(), vec.end());
    int M = vec.size();
    assert(M <= 100);
    MaxClique mc(M);
    for (int i = 0; i < M; ++i) {
      for (int j = i + 1; j < M; ++j) {
        int x = vec[i], y = vec[j];
        bool diff = false;
        for (auto e : edge) {
          diff |= e.first == x && e.second == y;
        }
        if (diff) {
          if (s[x] == s[y]) {
            mc.AddEdge(i, j);
          }
        } else {
          if (s[x] != s[y]) {
            mc.AddEdge(i, j);
          }
        }
      }
    }
    vector<int> ans = mc();
    for (int& u : ans) u = vec[u];
    return ans;
  };

  vector<vector<int>> nd(P);
  for (int i = 0; i < N; ++i) {
    nd[s[i]].push_back(i);
  }
  vector<int> vec;
  vector<int> ans;
  for (int i = 0; i < P; ++i) {
    vector<int> v;
    int x = -1;
    int cnt = 0;
    int ocnt = 0;
    for (int u : nd[i]) {
      if (!vis[u]) {
        if (x == -1) x = u;
      } else {
        v.push_back(u);
        cnt++;
      }
      if (out[u]) {
        ocnt++;
      }
    }
    if (cnt == 0) {
      ans.push_back(nd[i][0]);
    } else if (ocnt == 0) {
      vector<int> w = Solve(v);
      ans.insert(ans.end(), w.begin(), w.end());
    } else {
      vec.insert(vec.end(), v.begin(), v.end());
      if (x != -1) {
        vec.push_back(x);
      }
    }
  }
  vec = Solve(vec);
  ans.insert(ans.end(), vec.begin(), vec.end());
  cout << ans.size() << "\n";
  for (int u : ans) cout << u + 1 << " ";
  cout << "\n";
}
