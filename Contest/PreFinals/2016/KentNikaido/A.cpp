#include <bits/stdc++.h>
using namespace std;

vector<string> t = { ".o..", ".ooo", "ooo.", "..o." };

int main() {
  int n; cin >> n;
  vector<string> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  int c = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i % 4 == 0 || i % 4 == 1) {
        if (v[i][j] == 'o') ++c;
      }
      if (t[i & 3][j & 3] == 'o' && v[i][j] == 'o') ++c;
    }
  }

  cout << (c & 1) << '\n';
}
