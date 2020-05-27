#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, l, r; cin >> n >> l >> r;
  unordered_map<int, unordered_map<int, int>> mp;
  while (n--) {
    int x, y, w; cin >> x >> y >> w;
    for (int xx = x - r; xx <= x + r; ++xx)
      for (int yy = y - r; yy <= y + r; ++yy) 
        mp[xx][yy] += w;
    for (int xx = x - l + 1; xx < x + l; ++xx)
      for (int yy = y - l + 1; yy < y + l; ++yy) 
        mp[xx][yy] -= w;
  }

  int mx = 0;
  for (auto &pp : mp) {
    for (auto &p : pp.second) {
      mx = max(mx, p.second);
      // cerr << pp.first << ' ' << p.first << " = " << p.second << endl;
    }
  }

  cout << mx << endl;

}
