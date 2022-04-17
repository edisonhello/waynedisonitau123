#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];
  sort(v.begin(), v.end());
  int an = v[0];
  for (int i : v) {
    an = an & i;
  }

  if (an != v[0]) {
    cout << -1 << '\n';
    return;
  }

  cout << 2 * n << '\n';
  for (int i = 0; i < n; ++i) {
    cout << v[i] << ' ' << v[0] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) solve();
}

