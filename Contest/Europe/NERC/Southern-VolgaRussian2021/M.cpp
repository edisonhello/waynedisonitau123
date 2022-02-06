#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <tuple>
#include <functional>
#include <iomanip>

using namespace std;

int main() {
  int t; cin >> t; while (t--) {
    int a, b; cin >> a >> b;

    if ((a + b) & 1) {
      cout << -1 << ' ' << -1 << '\n';
    } else {
      cout << a - (a / 2) << ' ' << b - (b + 1) / 2 << '\n';
    }
  }
}

