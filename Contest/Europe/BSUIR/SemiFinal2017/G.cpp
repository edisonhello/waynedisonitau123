#include <iostream>
using namespace std;

__int128 Euclid(__int128 a, __int128 b, __int128 c, __int128 n) {
  if (a >= c || b >= c) {
    return (a / c) * (n * (n + 1) / 2) + (b / c) * (n + 1) +
           Euclid(a % c, b % c, c, n);
  }
  if (n < 0 || a == 0) return 0;
  __int128 m = (a * n + b) / c;
  return n * m - Euclid(c, c - b - 1, a, m - 1);
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int a, b, m, k;
    cin >> a >> b >> m >> k;
    __int128 sum = (a + (a + static_cast<__int128>(k - 1) * b)) * k / 2 - m * Euclid(b, a, m, k - 1);
    if (sum == 0) {
      cout << "0\n";
    } else if (sum % 9 == 0) {
      cout << "9\n";
    } else {
      cout << static_cast<int>(sum % 9) << "\n";
    }
  }
}
