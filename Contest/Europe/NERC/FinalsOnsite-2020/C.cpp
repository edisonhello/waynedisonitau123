#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    vector<vector<int>> g(N);
    vector<int> st, ed;
    for (int i = 0; i < M; ++i) {
      int S;
      cin >> S;
      vector<int> p(S);
      for (int j = 0; j < S; ++j) {
        cin >> p[j];
        p[j]--;
      }
      for (int j = 0; j + 1 < S; ++j) {
        st.push_back(p[j]);
        ed.push_back(p[j + 1]);
      }
    }
    M = st.size();
    for (int i = 0; i < M; ++i) {
      g[st[i]].push_back(i);
      g[ed[i]].push_back(i);
    }

    vector<bool> vis(N), tree(M);
    vector<int> dep(N), fa(N, -1), fe(N, -1);

    auto Dfs = [&](auto dfs, int x) -> void {
      vis[x] = true;
      for (int e : g[x]) {
        int u = st[e] ^ ed[e] ^ x;
        if (vis[u]) continue;
        tree[e] = true;
        dep[u] = dep[x] + 1;
        fa[u] = x;
        fe[u] = e;
        dfs(dfs, u);
      }
    };

    Dfs(Dfs, 0);
    vector<bool> covered(M);

    for (int i = 0; i < M; ++i) {
      if (tree[i]) continue;
      int x = st[i], y = ed[i];
      if (dep[x] < dep[y]) swap(x, y);
      while (x != y) {
        assert(!covered[fe[x]]);
        covered[fe[x]] = true;
        x = fa[x];
      }
    }
    vector<vector<int>> g2(N);
    for (int i = 0; i < M; ++i) {
      if (tree[i] && !covered[i]) {
        g2[st[i]].push_back(i);
        g2[ed[i]].push_back(i);
      }
    }
    vector<bool> trim(M);
    vector<bool> done(N);
    vector<bool> matched(N);

    auto DfsTrim = [&](auto dfs, int x, int p = -1) -> void {
      done[x] = true;
      for (int e : g2[x]) {
        int u = st[e] ^ ed[e] ^ x;
        if (u == p) continue;
        dfs(dfs, u, x);
        if (g2[x].size() % 2 == 1 && g2[u].size() % 2 == 1 && !matched[u] && !matched[x]) {
          matched[u] = true;
          matched[x] = true;
          trim[e] = true;
        }
      }
    };

    for (int i = 0; i < N; ++i) {
      if (done[i]) continue;
      DfsTrim(DfsTrim, i);
    }
    fill(done.begin(), done.end(), false);
    for (int i = 0; i < N; ++i) {
      g2[i].clear();
    }
    for (int i = 0; i < M; ++i) {
      if (tree[i] && !covered[i] && !trim[i]) {
        g2[st[i]].push_back(ed[i]);
        g2[ed[i]].push_back(st[i]);
      }
    }
    vector<int> dp(N), ep(N, -1);
    vector<pair<int, int>> ans;

    auto DfsDp = [&](auto dfs, int x, int p = -1) -> void {
      dp[x] = 0;
      done[x] = true;
      vector<int> child;
      for (int u : g2[x]) {
        if (u == p) continue;
        dfs(dfs, u, x);
        dp[x] += dp[u];
        child.push_back(u);
      }
      for (int i = 0; i + 1 < child.size(); i += 2) {
        ans.emplace_back(ep[child[i]], ep[child[i + 1]]);
        dp[x]--;
      }
      if (child.size() % 2 == 0) {
        if (p != -1) dp[x]++;
        ep[x] = x;
      } else {
        ep[x] = ep[child.back()];
      }
    };

    for (int i = 0; i < N; ++i) {
      if (done[i]) continue;
      DfsDp(DfsDp, i);
      if (ep[i] != i) ans.emplace_back(ep[i], i);
    }
    cout << ans.size() << "\n";
    for (auto [u, v] : ans) cout << u + 1 << " " << v + 1 << "\n";
  }
}
