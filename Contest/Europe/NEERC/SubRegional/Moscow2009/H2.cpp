#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("harmless.in", "r", stdin);
  freopen("harmless.out", "w", stdout);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> pref(n, vector<int>(m));
  vector<vector<int>> rank(m, vector<int>(n));
  vector<vector<int>> rev(n, vector<int>(m));
  vector<vector<int>> trev(m, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> pref[i][j];
      pref[i][j]--;
      rev[i][pref[i][j]] = j;
    }
  }
  vector<vector<bool>> inc(m, vector<bool>(n));
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> ptr(m);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> rank[i][j];
      rank[i][j]--;
      trev[i][rank[i][j]] = j;
    }
    for (int j = 0; j < k; ++j) {
      inc[i][rank[i][j]] = true;
      pq.emplace(rev[rank[i][j]][i], rank[i][j]);
    }
    ptr[i] = k;
  }
  // cerr << "ok" << endl;
  vector<int> used(n, m);
  vector<vector<bool>> have(m, vector<bool>(n));
  vector<vector<int>> res(m);
  while (!pq.empty()) {
    while (!pq.empty() && used[pq.top().second] <= pq.top().first) pq.pop();
    if (pq.empty()) break;
    int r = pq.top().first;
    vector<pair<int, int>> pushed;
    // cerr << "Round start" << endl;
    while (!pq.empty()) {
      int x = pq.top().first;
      int y = pq.top().second;
      if (x != r) break;
      pq.pop();
      if (used[y] <= x) continue;
      int g = -1;
      int z = pref[y][x];
      // cerr << y + 1 << " -> " << z + 1 << " " << x << endl;
      if (used[y] < m) {
        assert(have[pref[y][used[y]]][y]);
        have[pref[y][used[y]]][y] = false;
        // g = pref[y][used[y]];
      }
      have[pref[y][x]][y] = true;
      used[y] = x;
      // cerr << "x = " << x << " y = " << y << endl;
      // cerr << "z = " << pref[y][x] << endl;
      for (int i = 0; i < m; ++i) {
        if (inc[i][y] && rev[y][i] > x) {
          inc[i][y] = false;
          while (ptr[i] < n && used[rank[i][ptr[i]]] <= rev[rank[i][ptr[i]]][i]) ptr[i]++;
          assert(ptr[i] < n);
          // cerr << "fac = " << i + 1 << ": " << rank[i][ptr[i]] + 1 << endl;
          inc[i][rank[i][ptr[i]]] = true;
          pushed.emplace_back(rev[rank[i][ptr[i]]][i], rank[i][ptr[i]]);
          ptr[i]++;
        }
      }
    }
    for (auto p : pushed) pq.emplace(p);
  }
  for (int i = 0; i < m; ++i) {
    // cerr << "size = " << res[i].size() << endl;
    vector<int> res;
    for (int j = 0; j < n; ++j) {
      if (have[i][rank[i][j]]) res.push_back(rank[i][j]);
    }
    assert(res.size() == k);
    for (int j = 0; j < k; ++j) {
      cout << res[j] + 1 << " \n"[j + 1 == k];
    }
  }
}
