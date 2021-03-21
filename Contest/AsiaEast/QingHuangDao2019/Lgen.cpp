#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int n = 10, l1 = 10, l2 = 10, l3 = 10, k = 10;
  cout << n << ' ' << l1 << ' ' << l2 << ' ' << l3 << ' ' << k << endl;
  while (k--) {
    int a = rand() % 3 + 1;
    if (a == 1){
      cout << a << ' ' << rand() % n + 1 << ' ' << rand() % l1 + 1 << endl;
    } else if (a == 2) {
      cout << a << ' ' << rand() % n + 1 << ' ' << rand() % l2 + 2 + l1 << endl;
    } else {
      cout << a << ' ' << rand() % n + 1 << ' ' << rand() % l3 + 3 + l1 + l2 << endl;
    }
  }
}
