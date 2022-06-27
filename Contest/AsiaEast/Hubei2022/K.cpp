#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    double c;
    cin >> c;
    if (n >= 10000000) {
      c += 2.0;
    } else if (n >= 9800000) {
      c += 1.0 + static_cast<double>(n - 9800000) / 200000;
    } else {
      c += static_cast<double>(n - 9500000) / 300000;
    }
    cout << fixed << setprecision(20) << max<double>(c, 0) << "\n";
  }
}
