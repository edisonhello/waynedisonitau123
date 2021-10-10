#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  int ca, cb, cc; cin >> ca >> cb >> cc;

  int x1, y1, x2, y2, x3, y3; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  
  bool flip = 0;
  if (y1 == y2 && y2 == y3) {
    flip = 1;
    swap(n, m);
    swap(x1, y1);
    swap(x2, y2);
    swap(x3, y3);
  }

  vector<vector<char>> mp(n, vector<char>(m, 0));

  bool sab = 0, sac = 0;
  if (y1 != y2 && y1 != y3);
  else if (y2 != y1 && y2 != y3) {
    swap(x1, x2);
    swap(y1, y2);
    swap(ca, cb);
    sab = 1;
  } else if (y3 != y1 && y3 != y2) {
    swap(x1, x3);
    swap(y1, y3);
    swap(ca, cc);
    sac = 1;
  }

  int dx = x1, dy = y1;
  x2 = (x2 - x1 + n) % n;
  y2 = (y2 - y1 + m) % m;
  x3 = (x3 - x1 + n) % n;
  y3 = (y3 - y1 + m) % m;
  x1 = y1 = 0;

  bool sbc = 0;
  if (make_pair(x3, y3) < make_pair(x2, y2)) {
    sbc = 1;
    swap(x2, x3);
    swap(y2, y3);
    swap(cb, cc);
  }

  mp[x1][y1] = 'A';
  mp[x2][y2] = 'B';
  mp[x3][y3] = 'C';

  --ca, --cb, --cc;
  for (int i = 1; i < n; ++i) if (ca > 0) {
    --ca;
    mp[i][0] = 'A';
  }

  for (int i = y2 - 1; i >= 0; --i) {
    if (mp[x2][i]) break;
    if (cb == 0) break;
    mp[x2][i] = 'B';
    --cb;
  }

  for (int i = y2 + 1; i < m; ++i) {
    if (mp[x2][i]) break;
    if (cb == 0) break;
    mp[x2][i] = 'B';
    --cb;
  }

  for (int i = x2 - 1; i >= 0; --i) {
    for (int j = 0; j < m; ++j) {
      if (mp[i][j]) break;
      if (cb == 0) break;
      if ((j > 0 && mp[i][j - 1] == 'B') || (mp[i + 1][j] == 'B')) {
        mp[i][j] = 'B';
        --cb;
      }
    }
  }

}

int main() {
  int t; cin >> t; while (t--) solve();
}
