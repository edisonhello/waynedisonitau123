#include <bits/stdc++.h>
using namespace std;

deque<int> want[100005];
deque<int> lst[100005];
int ftook[100005];
vector<int> accept[100005];
int gotjob[100005];
set<int> inside[100005];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  freopen("harmless.in", "r", stdin);
  freopen("harmless.out", "w", stdout);

  int n, m, k; cin >> n >> m >> k;
  vector<vector<int>> pos(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      int t; cin >> t;
      want[i].push_back(t);
      pos[i][t] = j + 1;
    }
  }

  vector<vector<int>> facpos(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= m; ++i) {
    for (int j = 0; j < n; ++j) {
      int t; cin >> t;
      lst[i].push_back(t);
      facpos[i][t] = j + 1;
    }
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= k; ++j) {
      pq.emplace(pos[lst[i].front()][i], lst[i].front());
      inside[lst[i].front()].insert(i);
      lst[i].pop_front();
    }
  }

  while (pq.size()) {
    auto [pri, pp] = pq.top(); pq.pop();
    int fac = want[pp][pri - 1];
    inside[pp].erase(fac);
    if (gotjob[pp]) {
      // if (lst[fac].size()) {
      //   pq.emplace(pos[lst[fac].front()][fac], lst[fac].front());
      //   lst[fac].pop_front();
      // }
    } else {
      accept[fac].push_back(pp);
      gotjob[pp] = 1;
      assert(ftook[fac] < k);
      ftook[fac]++;
      for (int _fac : inside[pp]) {
        while (lst[_fac].size()) {
          if (gotjob[lst[_fac].front()]) {
            lst[_fac].pop_front();
            continue;
          }
          pq.emplace(pos[lst[_fac].front()][_fac], lst[_fac].front());
          inside[lst[_fac].front()].insert(_fac);
          lst[_fac].pop_front();
          break;
        }
      }
    }
  }

  for (int i = 1; i <= m; ++i) assert((int)accept[i].size() == k);

  for (int i = 1; i <= m; ++i) {
    sort(accept[i].begin(), accept[i].end(), [&] (int pa, int pb) {
      return facpos[i][pa] < facpos[i][pb];
    });
    for (int i : accept[i]) cout << i << ' ';
    cout << '\n';
  }
}
