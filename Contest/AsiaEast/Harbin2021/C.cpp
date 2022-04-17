#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<set<int>> g(N);
  vector<int> fa(N, -1);
  for (int i = 1; i < N; ++i) {
    int p;
    cin >> p;
    g[p - 1].insert(i);
    fa[i] = p - 1;
  }
  vector<int> c(N);
  for (int i = 0; i < N; ++i) {
    cin >> c[i];
    c[i]--;
  }

  vector<int> que;
  for (int i = 0; i < N; ++i) {
    if (g[i].size() == 1 && fa[i] != -1) {
      que.push_back(i);
    }
  }
  for (int iter = 0; iter < que.size(); ++iter) {
    int x = que[iter];
    assert(g[x].size() == 1);
    int u = *g[x].begin();
    g[fa[x]].erase(x);
    g[fa[x]].insert(u);
    fa[u] = fa[x];
  }

  vector<map<int, int>> dp(N);
  vector<int> best(N);
  vector<int> sz(N);
  vector<int> tag(N);
  vector<int> min_key(N);

  auto Dfs = [&](auto self, int x) -> void {
    sz[x] = 1;
    int to = -1;
    for (int u : g[x]) {
      self(self, u);
      sz[x] += sz[u];
      if (to == -1 || sz[u] > sz[to]) {
        to = u;
      }
    }
    if (g[x].empty()) {
      best[x] = 1;
      dp[x][c[x]] = 0;
      min_key[x] = c[x];
    } else {
      dp[x].swap(dp[to]);
      tag[x] = tag[to];
      vector<int> tc;
      int s = best[to];
      set<int> tt;
      for (int u : g[x]) {
        if (u == to) {
          continue;
        }
        for (auto iter : dp[u]) {
          if (tag[u] + iter.second < best[u]) {
            if (tt.count(iter.first) == 0 && dp[x].find(iter.first) != dp[x].end()) {
              int q = min(best[to], dp[x][iter.first] + tag[to]);
              dp[x][iter.first] = q - tag[to];
            }
            if (dp[x].find(iter.first) == dp[x].end()) {
              dp[x][iter.first] = s - tag[x];
            }
            dp[x][iter.first] += tag[u] + iter.second;
            dp[x][iter.first] -= best[u];
          }
          tc.push_back(iter.first);
        }
        s += best[u];
        tag[x] += best[u];
      }
      best[x] = 1E9;
      tc.push_back(min_key[to]);
      for (int k : tc) {
        if (dp[x].find(k) == dp[x].end()) {
          dp[x][k] = s - tag[x];
        }
        if (dp[x][k] + tag[x] + 1 < best[x]) {
          best[x] = dp[x][k] + tag[x] + 1;
          min_key[x] = k;
        }
      }
      for (int k : tc) {
        dp[x][k] = min(dp[x][k], best[x] - tag[x]);
      }
      // for (auto& iter : dp[x]) {
      //   iter.second = min(iter.second, best[x] - tag[x]);
      // }
    }
  };

  Dfs(Dfs, 0);
  cout << best[0] << "\n";
  return 0;
}

