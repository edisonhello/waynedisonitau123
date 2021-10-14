#include <bits/stdc++.h>
using namespace std;

int rs() {
  return rand() % 201 - 100;
}

int64_t rx() {
  return 1ll * rand() * rand() % 20000000000000001 - 10000000000000000;
}

int main() {
  srand(time(0) * clock());

  int t = 200;
  while (t--) {
    int x = rs(), y = rs();
    while (abs(x) + abs(y) < 2) x = rs(), y = rs();
    cout << x << ' ' << y << ' ' << rx() << ' ' << rx() << endl;
  }
}
