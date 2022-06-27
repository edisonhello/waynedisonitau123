#include <bits/stdc++.h>
using namespace std;
#define ll int64_t

int main() {
  int t;
  cin >> t;
  while (t--) {
    ll a, b, x, y;
    cin >> x >> y >> a >> b;
    ll ga = __gcd(a, b);
    ll gx = __gcd(x, y);
    a /= ga, b /= ga;
    x /= gx, y /= gx;

    int ans = 1;
    while (x != 0 && y != 0) {
      if (x > y) swap(x, y);
      // cout << "x y a b " << x << ' ' << y << ' ' << a << ' ' << b << endl;
      if ((x + y) % (a + b)) {
        ans = -1;
        break;
      }
      if (x % a == 0) {
        ll k = x / a;
        ll t = (x + y) / (a + b);
        x = k, y = t - k, ++ans;
      } else if (y % a == 0) {
        ll k = y / a;
        ll t = (x + y) / (a + b);
        x = k, y = t - k, ++ans;
      } else {
        ans = -1;
        break;
      }
    }

    cout << ans << '\n';
  }
}

