#include <bits/stdc++.h>
using namespace std;

string solve() {
  int x, y; cin >> x >> y;
  string s; cin >> s;

  if (x == 0 && y == 0) return "Impossible";

  int l = 0, r = 0, u = 0, d = 0;
  for (char c : s) {
    if (c == 'L') ++l;
    if (c == 'R') ++r;
    if (c == 'U') ++u;
    if (c == 'D') ++d;
  }

  // cerr << "l r u d " << l << ' ' << r << ' ' << u << ' ' << d << endl;

  string ans;
  if (x > 0) {
    while (l > 0) ans += "L", ++x, --l;
  } else if (x < 0) {
    while (r > 0) ans += "R", --x, --r;
  } else if (l) {
    while (l > 0) ans += "L", ++x, --l;
  } else if (r) {
    while (r > 0) ans += "R", --x, --r;
  }

  if (y > 0) {
    while (d > 0) ans += "D", ++y, --d;
  } else if (y < 0) {
    while (u > 0) ans += "U", --y, --u;
  } else if (d) {
    while (d > 0) ans += "D", ++y, --d;
  } else if (u) {
    while (u > 0) ans += "U", --y, --u;
  }

  // cerr << "nxy dxy " << nx << ' ' << ny << ", " << dx << ' ' << dy << endl;

  if (x == 0) {
    if (abs(y) <= u + d) return "Impossible";
    while (u > 0) ans += "U", --u;
    while (d > 0) ans += "D", --d;
    return ans;
  }
  if (y == 0) {
    if (abs(x) <= l + r) return "Impossible";
    while (l > 0) ans += "L", --l;
    while (r > 0) ans += "R", --r;
    return ans;
  }

  if (x > 0) {
    if (r != x) {
      while (r > 0) ans += "R", --r;
      while (u > 0) ans += "U", --u;
      while (d > 0) ans += "D", --d;
      return ans;
    }
  } else {
    if (l != -x) {
      while (l > 0) ans += "L", --l;
      while (u > 0) ans += "U", --u;
      while (d > 0) ans += "D", --d;
      return ans;
    }
  }
  if (y > 0) {
    if (y != u) {
      while (u > 0) ans += "U", --u;
      while (l > 0) ans += "L", --l;
      while (r > 0) ans += "R", --r;
      return ans;
    }
  } else {
    if (d != -y) {
      while (d > 0) ans += "D", --d;
      while (l > 0) ans += "L", --l;
      while (r > 0) ans += "R", --r;
      return ans;
    }
  }
  return "Impossible";
}

int main() {
  int t; cin >> t; while (t--) {
    string ans = solve();
    cout << ans << '\n';
  }
}
