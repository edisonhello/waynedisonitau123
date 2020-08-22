#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("laboratory.in", "r", stdin);
  freopen("laboratory.out", "w", stdout);
  int n;
  cin >> n;

  map<string, int> po;

  auto GetID = [&](const string &s) {
    if (po.find(s) != po.end()) return po[s];
    int res = po.size();
    po[s] = res;
    return res;
  };

  vector<tuple<int, int, int>> cubes;
  for (int i = 0; i < n; ++i) {
    string a, b, c;
    cin >> a >> b >> c;
    if (a == b || a == c || b == c) continue;
    int x = GetID(a);
    int y = GetID(b);
    int z = GetID(c);
    cubes.emplace_back(x, y, z);
  }
  sort(cubes.begin(), cubes.end());

  auto Find = [&](int x, int y, int z) {
    return binary_search(cubes.begin(), cubes.end(), make_tuple(x, y, z)) ||
           binary_search(cubes.begin(), cubes.end(), make_tuple(y, z, x)) ||
           binary_search(cubes.begin(), cubes.end(), make_tuple(z, x, y));
  };

  for (int i = 0; i < cubes.size(); ++i) {
    for (int j = i + 1; j < cubes.size(); ++j) {
      auto [a, b, c] = cubes[i];
      auto [d, f, e] = cubes[j];
      if (a == d || a == e || a == f) continue;
      if (b == d || b == e || b == f) continue;
      if (c == d || c == e || c == f) continue;
      for (int k = 0; k < 3; ++k) {
        if (Find(b, d, c) && Find(a, f, b) && Find(a, e, f) && Find(a, c, e) &&
            Find(c, d, e) && Find(b, f, d)) {
          cout << "YES\n";
          return 0;
        }
        int t = f;
        f = e;
        e = d;
        d = t;
      }
    }
  }
  cout << "NO\n";
  return 0;
}
