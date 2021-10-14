#include <bits/stdc++.h>
using namespace std;


int main() {
  int n; cin >> n;
  vector<int64_t> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  __int128 mnop = LLONG_MAX;
  for (int z = 0; z <= 60; ++z) {
    vector<int64_t> vv;
    __int128 opc = 0;
    int64_t t_twoadj = 0;
    for (auto i : v) {
      if (z == 0) {
        if (!(i & 1)) {
          ++opc;
          if (i != 0) t_twoadj = 1;
          vv.push_back(i + 1);
        } else vv.push_back(i);
      } else {
        if (!(i & (1ll << z))) {
          int64_t y = i & ((1ll << z) - 1);
          int64_t add = (1ll << z) - y;
          int64_t sub = y + 1;
          if (sub <= add && (i - sub) >= 0) {
            opc += sub;
            vv.emplace_back(i - sub);
          } else {
            opc += add;
            vv.emplace_back(i + add);
          }
          // if (add == sub) t_twoadj = 1;
        } else vv.emplace_back(i);
      }
    }

    int64_t xs = 0;
    for (auto i : vv) xs ^= i;

    if (xs) {
      mnop = min(mnop, opc);
    } else {
      if (t_twoadj) {
        mnop = min(mnop, opc);
      } else {
        if (z == 0) mnop = min(mnop, opc + 2);
        else mnop = min(mnop, opc + 1);
      }
    }
  }

  cout << (long long)mnop << endl;
}
