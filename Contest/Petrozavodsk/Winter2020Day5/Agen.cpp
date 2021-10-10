#include <bits/stdc++.h>
using namespace std;


int main() {
  srand(time(0) * clock());
  int n = 20, m = 11;
  cout << n << ' ' << m << endl;

  for (int i = 0; i < m; ++i) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    random_shuffle(v.begin(), v.end());

    for (int j : v) cout << j << ' ';
    cout << endl;
  }
}
