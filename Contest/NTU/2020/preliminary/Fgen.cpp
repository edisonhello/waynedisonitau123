#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 50, m = 50;
  cout << n << " " << m << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << rand() % 10 - 5 << " ";
    }
    cout << endl;
  }
}
