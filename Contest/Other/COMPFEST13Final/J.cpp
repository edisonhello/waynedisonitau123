#include <bits/stdc++.h>
using namespace std;

int mp[1005][1005];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int n, m, k; cin >> n >> m >> k;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> mp[i][j];
    }
  }

  for (int z = 0; z < k; ++z) {
    int i = 1, j;
    cin >> j;

    while (i <= n) {
      int o = mp[i][j];
      mp[i][j] = 2;
      
      if (o == 1) ++j;
      else if (o == 2) ++i;
      else --j;
    }

    cout << j << ' ';
  }
}
