#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock());
  int n = 6, m = 3, k = 2;
  cout << n << ' ' << m << ' ' << k << endl;

  for (int i = 1; i <= n; ++i) {
    vector<int> v(m);
    iota(v.begin(), v.end(), 1);
    random_shuffle(v.begin(), v.end());
    for (int i : v) cout << i << ' ';
    cout << endl;
  }

  for (int i = 1; i <= m; ++i) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    random_shuffle(v.begin(), v.end());
    for (int i : v) cout << i << ' ';
    cout << endl;
  }
}
