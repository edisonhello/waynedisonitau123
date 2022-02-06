#include <bits/stdc++.h>
using namespace std;
#define int int64_t

bool check(int a, int b, int x) {
  if (b > a) return check(b, a, x);
  if (x > a) return false;
  if (a == x || b == x) return true;
  if (b == 0) return false;

  int to = a % b;
  if (x % b == to && a >= x && x >= to) return true;
  return check(b, to, x);
}


int32_t main() {
  int t; cin >> t; while (t--) {
    int a, b, x;
    cin >> a >> b >> x;
    if (check(a, b, x)) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
}
