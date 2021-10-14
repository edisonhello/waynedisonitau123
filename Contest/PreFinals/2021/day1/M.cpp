#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, L;
  cin >> N >> L;
  vector<string> s(N);
  for (int i = 0; i < N; ++i) {
    cin >> s[i];
    assert(s[i].size() == L);
  }
  vector<vector<int>> diff(N, vector<int>(L, L));
  for (int i = 0; i + 1 < N; ++i) {
    int last = L;
    for (int j = L - 1; j >= 0; --j) {
      if (s[i][j] != s[i + 1][j]) last = j;
      diff[i][j] = last;
    }
  }
  int x = -1, y = L;
  for (int i = 0; i < L; ++i) {
    int t = i;
    bool ok = true;
    for (int j = 0; j + 1 < N; ++j) {
      t = max(t, diff[j][i]);
      if (diff[j][i] < L && s[j][diff[j][i]] > s[j + 1][diff[j][i]]) ok = false;
    }
    if (t == L) ok = false;
    if (ok) {
      if (t - i < y - x) {
        x = i;
        y = t;
      }
    }
  }
  cout << x + 1 << " " << y + 1 << "\n";
}
