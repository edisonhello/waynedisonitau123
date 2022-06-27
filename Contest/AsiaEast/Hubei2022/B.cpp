#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int64_t x, y, a, b;
    cin >> x >> y >> a >> b;
    assert(a == 1 && b == 1);
    int ans = 1;
    bool bad = false;
    int64_t g = __gcd(x, y);
    x /= g;
    y /= g;
    while (true) {
      if (x == 1 && y == 0 || x == 0 && y == 1) {
        break;
      }
      if (x >= y) {
        if ((x - y) % 2 != 0) {
          bad = true;
          break;
        }
        x = (x - y) / 2;
      } else {
        if ((y - x) % 2 != 0) {
          bad = true;
          break;
        }
        y = (y - x) / 2;
      }
      ans++;
    }
    if (bad) {
      ans = -1;
    }
    cout << ans << "\n";
  }
}
