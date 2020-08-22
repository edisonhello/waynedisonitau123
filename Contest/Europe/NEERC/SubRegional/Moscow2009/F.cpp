#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("farm.in", "r", stdin);
  freopen("farm.out", "w", stdout);
  int n;
  cin >> n;
  int t = n / 4;
  if (n % 4 == 1) {
    cout << 1LL * 2 * t * t + t - 1 << ".5\n";
  } else if (n % 4 == 0) {
    cout << 1LL * 2 * t * t << ".0\n";
  } else if (n % 4 == 2) {
    cout << 1LL * 2 * t * t + 2 * t << ".0\n";
  } else {
    cout << 1LL * 2 * t * t + 3 * t << ".5\n";
  }
}
