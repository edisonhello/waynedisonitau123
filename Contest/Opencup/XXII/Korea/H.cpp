#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<pair<int, int>> ig[1000006];
vector<pair<int, int>> igr[1000006];

int32_t main() {
  int n, l, t;
  cin >> n >> l >> t;

  int smx = t / l;
  int left = t % l;

  pair<int, int> limit(smx, left);

  for (int i = 0; i < l; ++i) {
    int u, v; cin >> u >> v;
    ig[v].emplace_back(u, i);
    if (i < left) {
      igr[v].emplace_back(u, i);
    }
  }

  vector<int> val(n + 2);
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
  }

  vector<int> has(n + 2);
  vector<pair<int, int>> dis(n + 2);
  priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> qu;

  for (int z = 0; z < 8; ++z) {

    fill(has.begin(), has.end(), 0);
    fill(dis.begin(), dis.end(), pair<int, int>(1'000'000'000'000'000'000, 0));
    while (qu.size()) qu.pop();

    for (int i = 1; i <= n; ++i) {
      if (val[i] & (1 << z)) {
        qu.emplace(pair<int, int>(0, -1), i);
        dis[i] = pair<int, int>(0, -1);
      }
    }

    while (qu.size()) {
      while (qu.size() && has[qu.top().second]) qu.pop();
      if (qu.empty()) break;

      auto [dist, now] = qu.top();
      has[now] = 1;

      for (auto [to, tt] : ig[now]) {
        if (has[to]) {
          continue;
        }

        pair<int, int> tod(dis[now].first + (tt <= dis[now].second), tt);

        if (tod >= limit) continue;

        if (tod < dis[to]) {
          dis[to] = tod;
          qu.emplace(dis[to], to);
        }
      }
    }

    for (int i = 1; i <= n; ++i) {
      if (has[i]) {
        val[i] |= 1 << z;
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << val[i] << ' ';
  }
  cout << endl;
}

