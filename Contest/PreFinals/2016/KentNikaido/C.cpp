#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int64_t> c(7);
  for (int i = 0; i < 7; ++i) cin >> c[i];
  if (c[0] == 0) {
    cout << "NO\n";
    return 0;
  }
  c[0]--;
  vector<int64_t> d(7);
  for (int i = 0; i < 7; ++i) {
    d[i] = c[0] + c[1] + c[3] + c[5] - c[2] - c[4] - c[6];
    int64_t x = c[0];
    for (int j = 0; j < 6; ++j) {
      c[j] = c[j + 1];
    }
    c[6] = x;
  }
  for (int i = 0; i < 7; ++i) {
    if (d[i] < 0) {
      cout << "NO\n";
      return 0;
    }
  }
  vector<int> uf = {0, 1, 2, 3, 4, 5, 6, 7};
  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };
  for (int i = 0; i < 7; ++i) {
    if (d[i] > 0) {
      int x = Find(i);
      int y = Find((i + 1) % 7);
      uf[x] = y;
    }
  }
  for (int i = 1; i < 7; ++i) {
    if (c[i] > 0) {
      if (Find(i) != Find(0)) {
        cout << "NO\n";
        return 0;
      }
    }
  }
  cout << "YES\n";
  return 0;
}
