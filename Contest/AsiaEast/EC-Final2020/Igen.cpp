#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());
  int n = rand() % 5 + 1;
  int m = rand() % 5 + 1;
  int V = rand() % 20 + 1;
  int K = rand() % 20 + 1;
  int D = rand() % 20 + 1;
  cout << n << ' ' << m << ' ' << V << ' ' << K << ' ' << D << endl;

  while (n--) {
    cout << rand() % 50 + 1 << ' ' << rand() % 50 + 1 << endl;
  }

  while (m--) {
    cout << rand() % 50 + 1 << ' ' << rand() % 50 + 1 << endl;
  }
}
