#include <bits/stdc++.h>
using namespace std;

int main() {
  int M, N;
  cin >> M >> N;
  vector<vector<int>> g(26, vector<int>(26));
  for (int i = 0; i < 26; ++i) {
    g[i][i] = 1;
  }
  for (int i = 0; i < M; ++i) {
    string a, b;
    cin >> a >> b;
    g[a[0] - 'a'][b[0] - 'a'] = 1;
  }
  for (int k = 0; k < 26; ++k) {
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        g[i][j] |= g[i][k] && g[k][j];
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    string a, b;
    cin >> a >> b;
    if (a.size() != b.size()) {
      cout << "no\n";
    } else {
      bool ans = true;
      for (int j = 0; j < a.size(); ++j) {
        ans &= g[a[j] - 'a'][b[j] - 'a'];
      }
      if (ans) cout << "yes\n";
      else cout << "no\n";
    }
  }
}

