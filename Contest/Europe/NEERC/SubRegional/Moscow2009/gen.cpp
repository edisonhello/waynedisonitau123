#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock());
  int n = 256; cout << n << endl;
  for (int i = 0; i < n; ++i) {
    cout << rand() % 20001 - 10000 << ' ' << rand() % 20001 - 10000 << ' ' << rand() % 100 + 1 << endl;
  }

  cout << rand() % 20001 - 10000 << ' ' << rand() % 20001 - 10000 << ' ' << 1 << '\n';
  cout << rand() % 20001 - 10000 << ' ' << rand() % 20001 - 10000 << ' ' << 1 << '\n';
}
