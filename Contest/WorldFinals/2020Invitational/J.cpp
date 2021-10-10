#include <bits/stdc++.h>
using namespace std;
#define ll int64_t
#define int int64_t

set<int> g[300005];
int p[300005], o[300005];

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq[300005];

void dfs(int now) {
  if (g[now].empty()) {
    pq[now].emplace(o[now], now);
    return;
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tmp;

  for (int i : g[now]) {
    dfs(i);
    if (pq[i].size() > tmp.size()) {
      tmp.swap(pq[i]);
    }
    while (pq[i].size()) {
      auto p = pq[i].top();
      pq[i].pop();
      tmp.push(p);
    }
  }

  int now$ = 0;
  int sons = g[now].size();
  int each = 0;

  while (tmp.size()) {
    auto p = tmp.top();
    tmp.pop();

    int who = p.second;
    int totneed = p.first;
    int more = totneed - each;
    int pay = more * sons;
    now$ += pay;
    each += more;
    pq[now].emplace(now$, who);
    if (g[now].count(who)) --sons;
  }

  pq[now].emplace(now$ + o[now], now);
}

int ans[300005];

int32_t main() {
  int n; cin >> n;

  for (int i = 1; i <= n; ++i) {
    cin >> p[i] >> o[i];
    g[p[i]].insert(i);
  }

  dfs(0);

  while (pq[0].size()) {
    auto p = pq[0].top();
    pq[0].pop();
    ans[p.second] = p.first;
  }

  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << '\n';
  }

}
