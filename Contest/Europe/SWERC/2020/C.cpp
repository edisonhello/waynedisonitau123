#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int x, y;
  cin >> x >> y;

  int n;
  cin >> n;

  vector<pair<double, double>> v(n);
  vector<tuple<double, int, int>> es;
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
    es.emplace_back(v[i].second * 2, n, i);
    es.emplace_back((x - v[i].first) * 2, n, i);
    es.emplace_back(v[i].first * 2, n + 1, i);
    es.emplace_back((y - v[i].second) * 2, n + 1, i);
  }


  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double d = hypot(v[i].first - v[j].first, v[i].second - v[j].second);
      es.emplace_back(d, i, j);
    }
  }

  sort(es.begin(), es.end());

  vector<int> djs(n + 10);
  iota(djs.begin(), djs.end(), 0);

  function<int(int)> F = [&](int x) { return djs[x] == x ? x : djs[x] = F(djs[x]); };
  auto U = [&](int x, int y) { djs[F(x)] = F(y); }; 

  for (auto [d, u, v] : es) {
    if (F(u) == F(v)) continue;
    U(u, v);
    if (F(n) == F(n + 1)) {
      cout << fixed << setprecision(12) << d / 2 << endl;
      exit(0);
    }
  }


}

