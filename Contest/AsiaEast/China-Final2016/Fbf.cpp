#include <bits/stdc++.h>
using namespace std;

bool inside(string temp, string st) {
  for (int i = 0; i < (int)st.size(); ++i) {
    if (st.substr(i, temp.size()) == temp) return true;
  }
  return false;
}

void solve() {
  int n; cin >> n;
  vector<string> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];
  string mn;
  for (int i = 0; i < (int)v[0].size(); ++i) {
    string cur;
    for (int j = i; j < (int)v[0].size(); ++j) {
      cur += v[0][j];
      bool yes = 1;
      for (int k = 1; k < n; ++k) {
        if (inside(cur, v[k])) {
          yes = 0;
          break;
        }
      }
      if (yes) {
        if (mn.empty()) mn = cur;
        else {
          if (cur.size() < mn.size()) mn = cur;
          else if (cur.size() == mn.size()) mn = min(mn, cur);
        }
      }
    }
  }

  if (mn.empty()) {
    cout << "Impossible" << endl;
  } else cout << mn << endl;
}

int main() {
  int t; cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";
    solve();
  }
}
