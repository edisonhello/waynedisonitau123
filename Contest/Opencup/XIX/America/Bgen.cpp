#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int n = rand() % 4 + 1;
  int m = rand() % 4 + 1;
  cout << n << ' ' << m << endl;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << "OX"[rand() & 1];
    }
    cout << endl;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << "OX"[rand() & 1];
    }
    cout << endl;
  }
}
