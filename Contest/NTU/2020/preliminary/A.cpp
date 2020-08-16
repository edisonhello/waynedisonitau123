#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int64_t x;
    cin >> x;
    if (x == 0 || x % 2 == 1) cout << 2 << "\n";
    else cout << 1 << "\n";
  }
}
