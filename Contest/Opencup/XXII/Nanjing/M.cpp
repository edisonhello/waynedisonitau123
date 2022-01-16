#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); 
  cin.tie(0);
  int t; cin >> t; while (t--) {
    int n; cin >> n;
    vector<int64_t> v(n);

    for (int i = 0; i < n; ++i) cin >> v[i];

    if (n == 1) {
      cout << v[0] << '\n';
      continue;
    }

    bool flag = 1;
    for (int i = 0; i < n; ++i) if (v[i] >= 0) flag = 0;

    if (flag) {
      for (int i = 0; i < n; ++i) v[i] *= -1;
    }

    int pos = 0, neg = 0;
    for (int i = 0; i < n; ++i) {
      if (v[i] >= 0) ++pos;
      if (v[i] <= 0) ++neg;
    }

    if (pos && neg) {
      int64_t s = 0;
      for (int i = 0; i < n; ++i) {
        s += abs(v[i]);
      }
      cout << s << '\n';
      continue;
    }

    int64_t mn = LLONG_MAX;
    int64_t sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += v[i];
      mn = min(mn, v[i]);
    }

    cout << sum - 2 * mn << '\n';
  }
}

