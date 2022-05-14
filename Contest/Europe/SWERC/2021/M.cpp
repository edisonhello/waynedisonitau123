#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t; while (t--) {
    int n, m; cin >> n >> m;
    vector<int> r(m), w(m);

    int R = 0, W = 0;
    for (int i = 0; i < m; ++i) {
      cin >> r[i] >> w[i];
      R = max(R, r[i]);
      W = max(W, w[i]);
    }

    if (R + W > n) {
      cout << "IMPOSSIBLE" << '\n';
    } else {
      for (int r = 0; r < R; ++r) cout << "R";
      for (int i = 0; i < n - R; ++i) cout << "W";
      cout << '\n';
    }
    
  }
}

