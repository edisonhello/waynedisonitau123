#include <bits/stdc++.h>
using namespace std;

string st[2555];

int main() {
  srand(time(0) * clock());
  int n = 2500;
  cout << n << endl;

  int len = 1000;
  for (int i = 0; i < len; ++i) st[0] += rand() % 26 + 'a';
  cout << st[0] << endl;

  for (int i = 1; i < n; ++i) {
    if (rand() & 1) {
      int x = rand() % i;
      cout << "SUB " << x << ' ';
      int l = rand() % st[x].size(), r = rand() % st[x].size();
      if (l > r) swap(l, r);
      cout << l << ' ' << r + 1 << endl;
      st[i] = st[x].substr(l, r - l + 1);
    } else {
      int a = rand() % i, b = rand() % i;
      cout << "APP ";
      cout << a << ' ' << b << endl;
      st[i] = st[a] + st[b];
    }
  }
}
