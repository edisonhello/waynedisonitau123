#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  vector<int> cnt(32, 0);
  for (int i = 0; i < n; ++i) {
    for (int z = 0; z < 31; ++z) {
      if (v[i] & (1 << z)) ++cnt[z];
    }
  }

  // for (int z = 29; z >= 0; --z) {
    while (true) {
      bool chg = false;
      // while (cnt[z] < cnt[z + 1]) {
      for (int y = 0; y < 30; ++y) {
        if (cnt[y] >= cnt[y + 1]) continue;
        int diff = cnt[y + 1] - cnt[y];
        int move = (diff + 2) / 3;
        chg = true;
        cnt[y] += move * 2;
        cnt[y + 1] -= move;
        // assert(cnt[y + 1] >= 0);
      }

      if (!chg) break;
    }
  // }

  for (int z = 0; z < 30; ++z) assert(cnt[z] >= cnt[z + 1]);

  cout << cnt[0] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) solve();
}

