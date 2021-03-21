#include <bits/stdc++.h>
using namespace std;

int Solve() {
  int N, M, K;
  cin >> N >> M >> K;
  vector<vector<int>> g(N);
  vector<int> st(M), ed(M);
  for (int i = 0; i < M; ++i) {
    cin >> st[i] >> ed[i];
    st[i]--;
    ed[i]--;
    g[st[i]].push_back(i);
    g[ed[i]].push_back(i);
  }
  constexpr int kP = 1'000'000'000 + 7;
  vector<vector<int>> dp(N, vector<int>(2));
  dp[0][1] = 1;
  for (int i = 1; i < N; ++i) {
    dp[i][0] = (1LL * (K - 2) * dp[i - 1][0] + 1LL * (K - 1) * dp[i - 1][1]) % kP;
    dp[i][1] = dp[i - 1][0]; 
  }

  vector<bool> pushed(M);
  vector<int> stk, dfn(N, -1), low(N);
  vector<int> which(M, -1);
  int stamp = 0, B = 0;

  auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
    dfn[x] = low[x] = stamp++;
    for (int e : g[x]) {
      if (e == p) continue;
      if (!pushed[e]) {
        pushed[e] = true;
        stk.push_back(e);
      }
      int u = st[e] ^ ed[e] ^ x;
      if (dfn[u] != -1) {
        low[x] = min(low[x], dfn[u]);
      } else {
        dfs(dfs, u, e);
        low[x] = min(low[x], low[u]);
        if (low[u] >= dfn[x]) {
          while (!stk.empty()) {
            int f = stk.back();
            stk.pop_back();
            which[f] = B;
            if (f == e) break;
          }
          B++;
        }
      }
    }
  };

  Dfs(Dfs, 0);

  vector<vector<int>> E(B);
  for (int i = 0; i < M; ++i) {
    assert(which[i] != -1);
    E[which[i]].push_back(i);
  }

  vector<bool> colored(B);
  vector<bool> inc(N);

  auto DfsColor = [&](auto dfs, int x) -> int {
    int res = 1;
    for (int e : g[x]) {
      int b = which[e];
      if (colored[b]) continue;
      colored[b] = true;
      
      vector<int> vtx;
      for (int f : E[b]) {
        if (!inc[st[f]]) {
          inc[st[f]] = true;
          vtx.push_back(st[f]);
        }
        if (!inc[ed[f]]) {
          inc[ed[f]] = true;
          vtx.push_back(ed[f]);
        }
      }
      for (int f : E[b]) inc[st[f]] = inc[ed[f]] = false;
      int V = E[b].size() == 1 ? 2 : E[b].size();
      assert(vtx.size() == V);
      int ways = dp[V - 1][0];
      for (int u : vtx) {
        if (u == x) continue;
        ways = 1LL * ways * dfs(dfs, u) % kP;
      }
      res = 1LL * res * ways % kP;
    }
    return res;
  };

  return 1LL * K * DfsColor(DfsColor, 0) % kP;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) cout << Solve() << "\n";
}
