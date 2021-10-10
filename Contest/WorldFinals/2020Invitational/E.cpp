#include <bits/stdc++.h>
using namespace std;


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int h, p;
    cin >> h >> p;
    int64_t ans = 0;

    int64_t solved = 0;
    int64_t total = (1ll << h) - 1;
    for (int i = 0; i < h; ++i) {
      if ((1ll << i) >= p) {
        ans += (total - solved) / p + !!((total - solved) % p);
        break;
      } else {
        ++ans;
        solved += 1ll << i;
      }
    }

    cout << ans << '\n';
  }
}
