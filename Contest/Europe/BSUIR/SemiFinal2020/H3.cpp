#include <bits/stdc++.h>
using namespace std;

int main() {
  int x, y;
  cin >> x >> y;
  int g = __gcd(x, y);
  x /= g;
  y /= g;
  if (y % 2 == 0) {
    cout << "-1\n";
    return 0;
  }
  if (y == 1) {
    cout << 1 << "\n";
    cout << x + x << "\n";
    return 0;
  }
  int k = 1;
  while ((k + 2) * y < 10000) k += 2;
  int n = (k * y + 1) / 2;
  int s = k * x;
  int p = 10000;
  vector<int> v;
  g = 0;
  while (s > 0) {
    while (p * (p - 1) / 2 > s) p--;
    int c = p * (p - 1) / 2;
    int r = s / c;
    s -= r * c;
    g += r * p;
    while (r--) v.push_back(p);
  }
  if (g <= 2 * n) {
    while (g < 2 * n) v.push_back(1), g++;
    cout << v.size() << "\n";
    for (int u : v) cout << u << " ";
    cout << "\n";
    return 0;
  } 
  assert(false);
}
