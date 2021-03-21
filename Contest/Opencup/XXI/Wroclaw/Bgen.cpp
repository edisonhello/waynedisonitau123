#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock() * clock());

  int t = 10;
  cout << t << endl;
  while (t--) {
    int n = rand() % 3 + 1;
    int m = rand() % 1000 + 1;
    cout << n << ' ' << m << endl;

    while (n--) {
      cout << rand() % 21 - 10 << ' ' << rand() % 21 - 10 << ' ' << rand() % 201 - 100 << endl;
    }
  }
}
