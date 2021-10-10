#include <bits/stdc++.h>
using namespace std;



int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<int> atk(n + m, 0);

  map<int, vector<pair<int, int>>> sx, sy;

  for (int i = 0; i < n; ++i) { 
    int x, y; cin >> x >> y;
    sx[x].emplace_back(y, i);
    sy[y].emplace_back(x, i);
  }
  for (int i = 0; i < m; ++i) {
    int x, y; cin >> x >> y;
    sx[x].emplace_back(y, i + n);
    sy[y].emplace_back(x, i + n);
  }

  for (auto &[_, v] : sx) {
    sort(v.begin(), v.end());
    for (int i = 1; i < (int)v.size(); ++i) {
      if ((v[i - 1].second < n) != (v[i].second < n)) {
        atk[v[i - 1].second] = 1;
        atk[v[i].second] = 1;
      }
    }
  }

  for (auto &[_, v] : sy) {
    sort(v.begin(), v.end());
    for (int i = 1; i < (int)v.size(); ++i) {
      if ((v[i - 1].second < n) != (v[i].second < n)) {
        atk[v[i - 1].second] = 1;
        atk[v[i].second] = 1;
      }
    }
  }

  for (int i = 0; i < n; ++i) cout << atk[i];
  cout << endl;

  for (int i = n; i < n + m; ++i) cout << atk[i];
  cout << endl;
}
