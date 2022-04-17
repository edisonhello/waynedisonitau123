#include <bits/stdc++.h>
using namespace std;

int main() {
  int d, v0, v1, v2, t;
  cin >> d >> v0 >> v1 >> v2 >> t;
  double ans = 0;
  if (v0 * t >= d) {
    ans = d;
  } else {
    double curt = 0;
    double pos = 0;
    int p = 0;
    while (true) {
      if (p == 0) {
        double nxtt = (1 + v2 * curt - pos) / (v2 - v1);
        if (1 + v1 * nxtt >= d) {
          nxtt = (d + v2 * curt - pos) / v2;
        }
        if (nxtt >= t) {
          ans = pos + v2 * (t - curt);
          break;
        }
        pos += v2 * (nxtt - curt);
        curt = nxtt;
        p ^= 1;
      } else {
        double nxtt = (v2 * curt + pos) / (v0 + v2);
        if (nxtt >= t) {
          ans = pos - v2 * (t - curt);
          break;
        }
        pos -= v2 * (nxtt - curt);
        curt = nxtt;
        p ^= 1;
      }
    }
  }
  cout << fixed << setprecision(20) << ans << endl;
}
