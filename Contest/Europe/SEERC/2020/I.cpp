#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> v(n);
  iota(v.begin(), v.end(), 1);
  int cnt = 0;
  do {
    int ok = 1;
    for (int i = 0; i < n; ++i) {
      int j = (i + 1) % n;
      if (v[i] % v[j] > 2) ok = 0;
    }
    if (ok) ++cnt;
  } while (next_permutation(v.begin(), v.end()));

  cout << cnt << endl;
}
