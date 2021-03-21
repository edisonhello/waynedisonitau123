#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  vector<int> st(M), ed(M);
  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    cin >> st[i] >> ed[i];
    st[i]--;
    ed[i]--;
    g[st[i]].push_back(i);
    g[ed[i]].push_back(i);
  }

  vector<int> stk, low(N), dfn(N, -1);
  vector<bool> pushed(M);
  int stamp = 0;

  constexpr int kP = 998244353;
  vector<int> pw(M + 1, 1);
  for (int i = 1; i <= M; ++i) pw[i] = (pw[i - 1] + pw[i - 1]) % kP;

  int res = 1;

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
          int cnt = 0;
          while (!stk.empty()) {
            int f = stk.back();
            stk.pop_back();
            cnt++;
            if (f == e) break;
          }
          if (cnt == 1) res = 2LL * res % kP;
          else res = 1LL * res * (pw[cnt] + kP - 1) % kP;
        }
      }
    }
  };

  for (int i = 0; i < N; ++i) {
    if (dfn[i] == -1) Dfs(Dfs, i);
  }
  cout << res << "\n";
  return 0;
}
