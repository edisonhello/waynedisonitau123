#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int a, b, n, m, h;
    cin >> a >> b >> n >> m >> h;
    int wd = n + m;

    auto Check = [&](int w) {
      int B = w - n;
      int T = m - B;
      int k = n / b;
      int64_t cnt = 1LL * k * (h - a);
      if (cnt >= T) {
        return true;
      }
      if (k * b + b > w) {
        return false;
      }
      cnt += (h - b);
      if (cnt >= T) {
        return true;
      }
      assert(w / b >= k + 1);
      cnt += 1LL * ((w / b) - (k + 1)) * (h - b);
      if (cnt >= T) {
        return true;
      } else {
        return false;
      }
    };

    for (int d = 30; d >= 0; --d) {
      if (wd - (1 << d) > n) {
        if (Check(wd - (1 << d))) {
          wd -= (1 << d);
        }
      }
    }
    cout << wd << "\n";
  }
}
