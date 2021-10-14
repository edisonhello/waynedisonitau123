#include <bits/stdc++.h>
using namespace std;

set<int> ok;

int main() {
  for (int x = 1; x <= 1000; ++x) {
    for (int y = 1; y < x; ++y) {
      for (int z = 1; z <= 1000; ++z) {
        int n = x * x - y * y + z * z;
        if (n >= 1 && n <= 1000) {
          ok.insert(n);
        }
      }
    }
  }

  cout << ok.size() << endl;
  for (int i = 0; i <= 1000; ++i) {
    if (ok.count(i) == 0) cout << i << endl;
  }
}
