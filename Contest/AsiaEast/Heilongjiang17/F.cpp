#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int g[7][7];
  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 7; ++j) {
      g[i][j] = (i == j ? 0 : 1000000);
    }
  }
  g[0][1] = g[1][0] = 1;
  g[0][2] = g[2][0] = 1;
  g[3][1] = g[1][3] = 1;
  g[3][2] = g[2][3] = 1;
  g[3][4] = g[4][3] = 1;
  g[3][5] = g[5][3] = 1;
  g[6][4] = g[4][6] = 1;
  g[6][5] = g[5][6] = 1;
  for (int k = 0; k < 7; ++k) {
    for (int i = 0; i < 7; ++i) {
      for (int j = 0; j < 7; ++j) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
  int T;
  cin >> T;
  while (T--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a < 1 || a > 7 || b < 1 || b > 7 || c < 1 || c > 7 || d < 1 || d > 7) {
      cout << "0\n";
    } else {
      a--;
      b--;
      c--;
      d--;
      cout << max(0, min(g[a][c] + g[b][d], g[a][d] + g[b][c])) << "\n";
    }
  }
}
