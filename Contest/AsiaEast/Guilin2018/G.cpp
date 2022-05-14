#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case " << T << ": ";
    int n; cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; ++i) cin >> v[i];

    sort(v.begin(), v.end());

    if (n == 1) {
      if (v[0] == 1) {
        cout << 1 << '\n';
        continue;
      } else {
        cout << 0 << '\n';
        continue;
      }
    }

    int g = 0;
    for (int i = 1; i < n; ++i) g = __gcd(v[i] - v[i - 1], g);

    if (g == 0) {
      if (v[0] == 1) {
        cout << 1 << '\n';
        continue;
      } else {
        cout << 0 << '\n';
        continue;
      }
    }

    if (g == 1) {
      cout << -1 << '\n';
      continue;
    }

    auto dist = [](int now, int tog) {
      return (tog - now % tog) % tog;
    };

    int64_t mn = 1e15;
    for (int i = 1; i * i <= g; ++i) {
      if (g % i == 0) {
        if (i != 1) mn = min<int64_t>(mn, dist(v[0], i));
        mn = min<int64_t>(mn, dist(v[0], g / i));
      }
    }

    cout << mn << '\n';
  }
}

