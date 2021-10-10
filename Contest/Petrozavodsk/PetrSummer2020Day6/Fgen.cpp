#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(0) * clock());
  int n = rand() % 2000 + 1;
  int k = rand() % (n + 1);
  int p = rand() % 200001 - 100000;

  vector<int> a(n), c(n);
  for (int i = 0; i < n; ++i) a[i] = rand() % 100001;
  for (int i = 0; i < n; ++i) c[i] = rand() % 200001 - 100000;

  sort(c.begin(), c.end());
  reverse(c.begin(), c.end());

  cout << n << ' ' << k << ' ' << p << endl;
  for (int i : a) cout << i << ' '; cout << endl;
  for (int i : c) cout << i << ' '; cout << endl;
}
