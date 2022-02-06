#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int solve(int k, int x) {
  if (x >= k * k) return 2 * k - 1;
  else if (x <= k * (k + 1) / 2) {
    int v = 0;
    for (int i = 30; i >= 0; --i) {
      int vv = v + (1 << i);
      if (vv * (vv + 1) / 2 >= x);
      else v = vv;
    }
    ++v;
    // return v * (v + 1) / 2;
    return v;
  } else {
    int v = 0;
    for (int i = 30; i >= 0; --i) {
      int vv = v + (1 << i);
      if (vv * (vv + 1) / 2 > k * k - x);
      else v = vv;
    }
    ++v;
    // return k * k - v * (v - 1) / 2;
    return 2 * k - v;
  }
}

int32_t main() {
  int t; cin >> t; while (t--) {
    int k, x; cin >> k >> x;

    cout << solve(k, x) << '\n';
  }
}

