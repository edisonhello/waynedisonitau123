#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock());
  int t = 10;
  cout << t << endl;

  while (t--) {
    int n = 1000, r = rand() % 20000;
    cout << n << ' ' << r << endl;

    while (n--) {
      int x = rand() % 40000, y = rand() % 40000;
      cout << x << ' ' << y << '\n';
    }
  }
}
