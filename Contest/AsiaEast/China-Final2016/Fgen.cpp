#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int t = 2; cout << t << endl;
  while (t--) {
    int n = rand() % 5 + 2;
    cout << n << endl;
    while (n--) {
      int l = rand() % 10 + 1;
      while (l--) {
        cout << char('a' + rand() % 5);
      }
      cout << endl;
    }
  }
}
