#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock());
  int n = rand() % 100 + 1;
  int r = rand() % 100 + 1;
  int l = rand() % r + 1;
  cout << n << ' ' << l << ' ' << r << endl;

  while (n--) {
    cout << rand() % 201 - 100 << ' ' << rand() % 201 - 100 << ' ' << rand() % 20001 - 10000 << endl;
  }
}
