#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());
  int n = 10;
  cout << n << endl;

  while (n--) {
    cout << rand() % 21 - 10 << ' ' << rand() % 21 - 10 << endl;
  }
}
