#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock());
  int t = 2;
  cout << t << endl;
  while (t--) {
    int n = rand() % 10 + 2, m = n - 1 + rand() % n;
    cout << n << ' ' << m << endl;
    for (int i = 1; i < n; ++i) {
      cout << i + 1 << ' ' << rand() % i + 1 << '\n';
    }
    for (int i = n - 1; i < m; ++i) {
      int u = rand() % n + 1, v = rand() % n + 1;
      cout << u << ' ' << v << '\n';
    }
  }
}
