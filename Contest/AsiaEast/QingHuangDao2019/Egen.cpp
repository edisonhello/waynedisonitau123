#include <bits/stdc++.h>
using namespace std;

int main() {
  int t = 1; cout << t << endl; while (t--) {
    int n = 100, m = 100, s = rand() % m + 1, t = rand() % m + 1;
    cout << n << ' ' << m << ' ' << s << ' ' << t << endl;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << 0;
      }
      cout << endl;
    }

    for (int i = 0; i < s; ++i) cout << i + 1 << ' ';
    cout << endl;

    for (int i = 0; i < t; ++i) cout << i + 1 << ' ';
    cout << endl;
  }
}
