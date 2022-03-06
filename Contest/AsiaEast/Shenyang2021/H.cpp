#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;
  vector<vector<int>> g(N);
  vector<int> st(M), ed(M), w(M);
  vector<int> edge(N);
  vector<int> uf(N);
  vector<int64_t> sum(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  for (int i = 0; i < M; ++i) {
    cin >> st[i] >> ed[i] >> w[i];
    st[i]--;
    ed[i]--;
    g[st[i]].push_back(i);
    g[ed[i]].push_back(i);
    int x = Find(st[i]);
    int y = Find(ed[i]);
    if (x != y) {
      uf[x] = y;
      edge[y] += edge[x];
      sum[y] += sum[x];
    }
    edge[y]++;
    sum[y] += w[i];
  }
  vector<vector<int>> nd(N);
  for (int i = 0; i < N; ++i) {
    nd[Find(i)].push_back(i);
  }

  vector<int> dfn(N, -1), low(N, -1);
  vector<bool> bridge(M);
  vector<int> bcc(N);
  vector<int> stk;
  vector<vector<int>> tree(N);
  vector<int> sbc(N);
  int stamp = 0, cnt = 0;

  auto Dfs = [&](auto dfs, int x, int p = -1, int pe = -1) -> void {
    dfn[x] = low[x] = stamp++;
    stk.push_back(x);
    // cerr << "x = " << x << "\n";
    for (int e : g[x]) {
      int u = st[e] ^ ed[e] ^ x;
      if (u == p) {
        continue;
      }
      if (dfn[u] == -1) {
        dfs(dfs, u, x, e);
        low[x] = min(low[x], low[u]);
      } else {
        low[x] = min(low[x], dfn[u]);
      }
    }
    if (low[x] == dfn[x]) {
      if (pe != -1) {
        bridge[pe] = true;
      }
      while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        bcc[u] = cnt;
        if (u == x) {
          break;
        }
      }
      cnt++;
    }
  };

  vector<int> sz(N);
  vector<int> par(N, -1);

  auto DfsTree = [&](auto dfs, int x, int p = -1) -> void {
    sz[x] = sbc[x];
    par[x] = p;
    for (int e : tree[x]) {
      int u = bcc[st[e]] ^ bcc[ed[e]] ^ x;
      if (u == p) {
        continue;
      }
      dfs(dfs, u, x);
      sz[x] += sz[u] + 1;
    }
  };

  int64_t ans = 0;

  for (int i = 0; i < N; ++i) {
    if (Find(i) == i) {
      if (edge[i] % 2 == 0) {
        ans += sum[i];
        continue;
      }
      stamp = 0;
      cnt = 0;
      Dfs(Dfs, i); 
      int bw = 1'000'000'000 + 1;
      for (int x : nd[i]) {
        for (int e : g[x]) {
          if (!bridge[e]) {
            bw = min(bw, w[e]);
          }
        }
      }
      for (int x : nd[i]) {
        for (int e : g[x]) {
          if (st[e] == x) {
            if (bcc[st[e]] != bcc[ed[e]]) {
              // cerr << bcc[st[e]] << " -> " << bcc[ed[e]] << endl;
              tree[bcc[st[e]]].push_back(e);
              tree[bcc[ed[e]]].push_back(e);
            } else {
              sbc[bcc[st[e]]]++;
            }
          }
        }
      }
      DfsTree(DfsTree, 0);
      for (int x : nd[i]) {
        for (int e : g[x]) {
          int u = bcc[st[e]];
          int v = bcc[ed[e]];
          if (u != v) {
            if (u == par[v]) {
              swap(u, v);
            }
            int a = sz[u];
            int b = sz[0] - 1 - sz[u];
            // cerr << "a = " << a << " b = " << b << endl;
            if (a % 2 == 0 && b % 2 == 0) {
              bw = min(bw, w[e]);
            }
          }
        }
      }
      for (int j = 0; j < cnt; ++j) {
        tree[j].clear();
        sbc[j] = 0;
      }
      ans += sum[i] - bw;
    }
  }
  cout << ans << "\n";
  return 0;
}
