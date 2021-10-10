#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());

  int n = 300000;
  cout << n << endl;
  
  for (int i = 1; i <= n; ++i) {
    cout << i - 1 << ' ' << rand() % 1000000 + 1 << endl;
  }
}
