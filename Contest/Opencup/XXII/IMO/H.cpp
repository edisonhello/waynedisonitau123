#include <bits/stdc++.h>
using namespace std;

void Solve(int K) {
  for (int n = 1; n <= 19; ++n) {
    for (int m = 1; n + m <= 19; ++m) {
      if (n * m == K) {
        cout << n + m + 1 << " " << (n + 1) * n / 2 + (m + 1) * m / 2 << "\n";
        for (int i = 0; i < n + 1; ++i) {
          for (int j = i + 1; j < n + 1; ++j) {
            cout << i + 1 << " " << j + 1 << "\n";
          }
        }
        for (int i = n; i < n + m + 1; ++i) {
          for (int j = i + 1; j < n + m + 1; ++j) {
            cout << i + 1 << " " << j + 1 << "\n";
          }
        }
        return;
      }
    }
  }
  for (int n = 2; n <= 20; ++n) {
    for (int v = 4; n + v <= 20; ++v) {
      if (n * (n - 1) / 2 + 4 * n + v - 1 == K) {
        cout << n + v << " " << n * (n - 1) / 2 + n * 2 + v - 1 << "\n";
        for (int i = 0; i < n; ++i) {
          for (int j = i + 1; j < n; ++j) {
            cout << i + 1 << " " << j + 1 << "\n";
          }
        }
        for (int i = 0; i < n; ++i) {
          cout << i + 1 << " " << n + 1 << "\n";
          cout << i + 1 << " " << n + v << "\n";
        }
        for (int i = 1; i < v; ++i) {
          cout << n + i << " " << n + i + 1 << "\n";
        }
        return;
      }
    }
  }
  assert(false);
}

int main() {
  int K;
  cin >> K;
  Solve(K);
}
