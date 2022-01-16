#include <bits/stdc++.h>
using namespace std;

namespace std {
  template<>
  struct hash<pair<int, int>> {
    int64_t operator()(const pair<int, int> &p) const {
      return INT_MAX * 1ll * p.first + p.second;
    }
  };
}

bool np[100005];

unordered_map<pair<int, int>, int> ans;

int dfs(int x, int y) { // x < y
  // cerr << "dfs to " << x << ' ' << y << endl;
  if (x == 0) return 1;
  if (x == 1) return 0;

  if (auto it = ans.find(pair{x, y}); it != ans.end())
    return it->second;

  vector<int> facs;

  int d = y - x;
  for (int i = 2; i * i <= d; ++i) {
    if (d % i == 0) {
      facs.push_back(i);
      while (d % i == 0) d /= i;
    }
  }
  if (d > 1) facs.push_back(d);

  // cerr << "d = " << d << " fac = ";
  // for (int i : facs) cerr << i << ' ' ;
  // cerr << endl;

  int mn = x - 1;
  for (int fac : facs) {
    int tolow = x % fac;
    int tohig = fac - tolow;
    //cerr << "x y fac tolow tohig " << x << ' ' << y << ' ' << fac << ' ' << tolow << ' ' << tohig << endl;
    if (fac == 2 && tolow == tohig) {
      mn = min(mn, dfs((x - 1) / 2, (y - 1) / 2) + 2);
      mn = min(mn, dfs((x + 1) / 2, (y + 1) / 2) + 2);
    } else if (tolow < tohig) {
      mn = min(mn, dfs((x - tolow) / fac, (y - tolow) / fac) + tolow + 1);
    } else {
      mn = min(mn, dfs((x + tohig) / fac, (y + tohig) / fac) + tohig + 1);
    }
  }

  // cerr  << x << ' ' << y << " is " << mn << endl;
  return ans[pair{x, y}] = mn;
}


int main() {
  int t; cin >> t; while (t--) {
    int x, y;
    cin >> x >> y;
    if (y < x) swap(x, y);
    cout << dfs(x, y) << '\n';
  }
}

