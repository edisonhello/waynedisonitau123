#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int r, b;
    cin >> r >> b;
    int x = r * (r - 1) / 2;
    int y = (r + b) * (r + b - 1) / 2;
    int g = __gcd(x, y);
    x /= g;
    y /= g;
    cout << "Case #" << tc << ": " << x << "/" << y << "\n";
  }
}

