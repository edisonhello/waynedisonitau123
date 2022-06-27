#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  int not1 = 0;
  for (int i : v) {
    if (i > 1) not1++;
  }

  if (n == 2) {
    cout << 1 << '\n';
    return;
  }

  cout << min(not1, n / 2) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) solve();
}

