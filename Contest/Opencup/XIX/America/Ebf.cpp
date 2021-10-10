#include <bits/stdc++.h>
using namespace std;

int v[22][22];

int main() {
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0 ; j < m; ++j) {
      cin >> v[i][j];
    }
  }

  int cnt = 0;
  for (int x = 1; x < (1 << n); ++x) {
    for (int y = 1; y < (1 << m); ++y) {
      vector<int> a, b;
      for (int i = 0; i < n; ++i) if (x & (1 << i)) a.push_back(i);
      for (int i = 0; i < m; ++i) if (y & (1 << i)) b.push_back(i);

      int ok = 1;
      for (int i : a) {
        for (int j = 2; j < (int)b.size(); ++j) {
          if ((v[i][b[j - 2]] < v[i][b[j - 1]]) != (v[i][b[j - 1]] < v[i][b[j]]))
            ok = 0;
        }
      }

      for (int j : b) {
        for (int i = 2; i < (int)a.size(); ++i) {
          if ((v[a[i - 2]][j] < v[a[i - 1]][j]) != (v[a[ i -1]][j] < v[a[i]][j]))
            ok = 0;
        }
      }

      if (ok) ++cnt;
    }
  }

  cout << cnt << endl;
}
