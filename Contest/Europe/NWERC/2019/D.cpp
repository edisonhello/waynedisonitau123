#include <bits/stdc++.h>
using namespace std;

#define Point pair<int, long long>

vector<pair<int, int>> g[2005];
long long dp[2005][10005];
bool use[2005], vis[2005];

Point Diff(Point a, Point b) {
  return Point(a.first - b.first, a.second - b.second);
}
__int128 Cross(Point a, Point b) {
  return (__int128)a.first * b.second - (__int128)b.first * a.second;
}
__int128 Cross(Point &ref, Point &a, Point &b) {
  return Cross(Diff(a, ref), Diff(b, ref));
}

void Dfs(int now, int s) {
  if (vis[now]) return;
  if (!s) return;
  vis[now] = 1;
  use[now] = 1;
  for (auto &p : g[now]) {
    if (vis[p.first]) continue;
    if (dp[p.first][s - 1] + p.second == dp[now][s]) {
      Dfs(p.first, s - 1);
    }
  }
}

int main() {
  int n, m; cin >> n >> m;
  while (m--) {
    int u, v, w; cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  memset(dp, 0x3f, sizeof(dp));
  dp[1][0] = 0;
  for (int s = 0; s <= 10000; ++s) {
    for (int i = 1; i <= n; ++i) {
      for (auto &p : g[i]) {
        long long z = dp[i][s] + p.second;
        if (z < dp[p.first][s + 1]) {
          dp[p.first][s + 1] = z;
        }
      }
    }
  }

  // cerr << "dp: " << endl;
  // for (int i = 1; i <= n; ++i) {
  //   for (int j = 0; j <= 6; ++j) {
  //     cerr << dp[i][j] << ' ';
  //   }
  //   cerr << endl;
  // }
  // cerr << "cf: " << endl;
  // for (int i = 1; i <= n; ++i) {
  //   for (int j = 0; j <= 6; ++j) {
  //     cerr << cf[i][j] << ' ';
  //   }
  //   cerr << endl;
  // }

  vector<pair<int, long long>> ps;
  for (int s = 1; s <= 10000; ++s) 
    if (dp[n][s] <= 10000000000000)
      ps.emplace_back(s, dp[n][s]);

  sort(ps.begin(), ps.end());
  vector<pair<int, long long>> cnt;
  for (auto &p : ps) {
    while (cnt.size() > 1u && Cross(cnt[cnt.size() - 2], p, cnt.back()) > 0) cnt.pop_back();
    if (cnt.empty() || cnt.back().second >= p.second) cnt.push_back(p);
  }

  // cerr << "count points: " << endl;
  // for (auto &p : cnt) {
  //   cerr << p.first << ' ' << p.second << endl;
  //   if (p.second >= 10) break;
  // }

  use[1] = use[n] = 1;  
  for (auto &p : cnt) {
    memset(vis, 0, sizeof(vis));
    Dfs(n, p.first);
    // int s = p.first;
    // int now = n;
    // while (s) {
    //   now = cf[now][s];
    //   --s;
    //   use[now] = 1;
    // }
  }

  vector<int> ans;
  for (int i = 1; i <= n; ++i) if (!use[i]) {
    ans.push_back(i);
  }

  cout << ans.size() << endl;
  for (int i : ans) cout << i << ' ';
  cout << endl;
}
