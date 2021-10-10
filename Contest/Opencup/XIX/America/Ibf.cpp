#include <bits/stdc++.h>
using namespace std;


int main() {
  int t; cin >> t;
  while (t--) {
    int k; string s;
    cin >> k >> s;

    int n = s.size();

    string mx;

    auto try_del = [&](vector<pair<int, int>> dels) {
      vector<int> z(s.size());
      for (auto [l, r] : dels) {
        for (int i = l; i <= r; ++i) z[i] = 1;
      }
      string ss;
      for (int i = 0; i < (int)s.size(); ++i) if (!z[i]) ss += s[i];
      mx = max(mx, ss);
    };

    auto f = [&](auto f, vector<pair<int, int>> dels) {
      try_del(dels);
      if (dels.size() == k) {
        return;
      }
      for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
          bool crx = 0;
          for (auto [ll, rr] : dels) {
            if (r < ll || rr < l);
            else crx = 1;
          }

          if (!crx) {
            dels.emplace_back(l, r);
            f(f, dels);
            dels.pop_back();
          }
        }
      }
    };

    f(f, vector<pair<int, int>>());

    cout << mx << endl;
  }
}
