#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int n = 2000, q = 2000;
  cout << n << ' ' << q << endl;

  while (n--) {
    cout << rand() % 2000000001 - 1000000000 << ' ';
    cout << rand() % 2000000001 - 1000000000 << '\n';
  }
}
