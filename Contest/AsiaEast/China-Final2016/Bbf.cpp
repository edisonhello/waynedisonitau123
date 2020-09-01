#include <bits/stdc++.h>
using namespace std;

bool pal(vector<int> &v) {
  for (int i = 0; i < ((int)v.size() >> 1); ++i) {
    if (v[i] != v[(int)v.size() - 1 - i]) return false;
  }
  return true;
}

int main() {
  int t; cin >> t; for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";
    int n; long long k; cin >> n >> k;
    long long c = 0;
    for (int i = 0; i < (1 << n); ++i) {
      vector<int> v, vv;
      for (int z = 0; z < n; z += 2) v.push_back(!!(i & (1 << z)));
      for (int z = 1; z < n; z += 2) vv.push_back(!!(i & (1 << z)));
      if (pal(v) || pal(vv)) {
        ++c;
        if (c == k) {
          for (int z = n - 1; z >= 0; --z) cout << !!(i & (1 << z));
          cout << endl;
          break;
        }
      }
    }
    if (c != k) {
      cout << "NOT FOUND!" << endl;
    }
  }
}
