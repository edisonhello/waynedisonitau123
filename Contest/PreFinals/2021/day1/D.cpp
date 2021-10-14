#include <bits/stdc++.h>
using namespace std;


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
  }

  double mn = 1e20;

  auto update = [&] (int x, int y) {
    double z = ((long long)x + y) / hypot(x, y);
    mn = min(mn, z);
  };

  sort(v.begin(), v.end());

  for (int i = 1; i < n; ++i) {
    auto [a, b] = v[i - 1];
    auto [c, d] = v[i];
    update(abs(a - c), abs(b - d));
  }

  for (auto &p : v) swap(p.first, p.second);

  sort(v.begin(), v.end());

  for (int i = 1; i < n; ++i) {
    auto [a, b] = v[i - 1];
    auto [c, d] = v[i];
    update(abs(a - c), abs(b - d));
  }

  cout << fixed << setprecision(12);
  cout << mn << endl;
}
