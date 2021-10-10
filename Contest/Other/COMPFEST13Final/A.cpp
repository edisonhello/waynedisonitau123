#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> mp(n);

  for (int i = 0; i < n; ++i) cin >> mp[i];

  vector<int> o(n);
  iota(o.begin(), o.end(), 0);
  sort(o.begin(), o.end(), [&](const int a, const int b) {
    for (int i = 0; i < m; ++i) {
      if (mp[a][i] != mp[b][i]) {
        if (i % 2 == 0) {
          return mp[a][i] < mp[b][i];
        } else {
          return mp[a][i] > mp[b][i];
        }
      }
    }
    return false;
  });

  for (int i : o) cout << i + 1 << ' ';
}
