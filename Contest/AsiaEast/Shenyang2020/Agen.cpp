#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock());

  int t = 1; 
  cout << t << endl;
  while (t--) {
    int xl = rand() % 20001 - 10000, xr = rand() % 20001 - 10000; if (xr < xl) swap(xl, xr); if (xl == xr) ++xr;
    int yl = rand() % 20001 - 10000, yr = rand() % 20001 - 10000; if (yr < yl) swap(yl, yr); if (yl == yr) ++yr;
    cout << xl << ' ' << yl << ' ' << xr << ' ' << yr << endl;

    for (int i = 0; i < 2; ++i) {
      while (true) {
        int xx = xr - xl + 1;
        int yy = yr - yl + 1;
        int x1 = rand() % xx + xl, x2 = rand() % xx + xl;
        int y1 = rand() % yy + yl, y2 = rand() % yy + yl;
        if (x1 == x2 && y1 == y2) continue;
        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
        break;
      }
    }
  }
}
