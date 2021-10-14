#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  if (n == 2 || n == 3 || n == 5) {
    cout << "impossible" << endl;
    exit(0);
  }

  if (n == 1) {
    cout << "1 1 1" << endl;
    cout << "A 0 0 U" << endl;
    exit(0);
  }

  int x = -1, y = -1, z = -1;
  for (int xx = 1; xx <= 1000; ++xx) for (int yy = 1; yy < xx; ++yy) for (int zz = 1; zz <= 1000; ++zz) {
    if (xx * xx - yy * yy + zz * zz == n) {
      x = xx, y = yy, z = zz;
      goto found;
    }
  }
  found:;

  assert(x != -1);

  int a = y, b = z, c = x * z;

  cout << a << ' ' << b << ' ' << c << endl;
  for (int Y = 0; Y <= x * z - y * z; Y += z) {
    for (int X = 0; X + Y < x * z; X += z) {
      if (Y > 0) {
        cout << "B " << X << ' ' << Y << ' ' << "D" << '\n';
      }
      if (Y < x * z - y * z) {
        cout << "B " << X << ' ' << Y << ' ' << "U" << '\n';
      }
    }
  }

  for (int Y = x * z - y * z; Y < c; Y += y) {
    for (int X = 0; X + Y < x * z; X += y) {
      if (Y > x * z - y * z) {
        cout << "A " << X << ' ' << Y << ' ' << "D" << '\n';
      }
      cout << "A " << X << ' ' << Y << ' ' << "U" << '\n';
    }
  }
}
