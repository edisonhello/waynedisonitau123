#include <bits/stdc++.h>
using namespace std;

int main() {
  int64_t x;
  cin >> x;
  if (x > 1 && (__builtin_popcountll(x - 1) == 1 || __builtin_popcountll(x) == 1)) cout << "Yes\n";
  else cout << "No" << "\n";
}
