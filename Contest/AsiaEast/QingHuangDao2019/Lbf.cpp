#include <bits/stdc++.h>
using namespace std;


int main() {
  int n, l1, l2, l3, k; cin >> n >> l1 >> l2 >> l3 >> k;
  vector<pair<int, int>> le, mi, ri;

  while (k--) {
    int a, x, y; cin >> a >> x >> y;
    (a == 1 ? le : a == 2 ? mi : ri).emplace_back(x, y);
  }

  int mn = INT_MAX;

  for (int z = 0; z < (1 << (int)mi.size()); ++z) {
    vector<int> l, r;
    for (int i = 0; i < (int)mi.size(); ++i) if (z & (1 << i)) {
      auto [x, y] = mi[i];
      l.push_back(y - 1 - l1 + x);
    } else {
      auto [x, y] = mi[i];
      r.push_back(l1 + l2 + 2 - y + x);
    }

    for (auto [x, y] : le) l.push_back(l1 + 1 - y + x);
    for (auto [x, y] : ri) r.push_back(y - 2 - l1 - l2 + x);

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int mx = 0;
    for (int i = 0; i < (int)l.size(); ++i) {
      mx = max(mx, l[i] - (i + 1) + (int)l.size());
    }
    for (int i = 0; i < (int)r.size(); ++i) {
      mx = max(mx, r[i] - (i + 1) + (int)r.size());
    }
    mn = min(mn, mx);
  }

  cout << mn << endl;
}
