#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  if (n == 1) {
    cout << "1\n1\n";
    return 0;
  }
  if (n == 2) {
    cout << "2\n1 1\n";
    return 0;
  }
  if (n % 2 == 1) {
    cout << 2 * n - 4 << "\n";
    for (int j = 0; j < 2; ++j) {
      for (int i = 2; i <= n - 1; ++i) {
        cout << i << " ";
      }
    }
    cout << "\n";
  } else {
    cout << 2 * n - 4 << "\n";
    for (int i = 2; i <= n - 1; ++i) {
      cout << i << " ";
    }
    for (int i = n - 1; i >= 2; --i) {
      cout << i << " ";
    }
    cout << "\n";
  }
}
