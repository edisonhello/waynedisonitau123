#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  auto b = a;
  sort(b.begin(), b.end());

  int l = 0;
  while (l < n && a[l] == b[l]) ++l;
  int r = n - 1;
  while (r >= 0 && a[r] == b[r]) --r;
  if (l == n) {
    cout << "1 1" << endl;
    exit(0);
  }
  for (int i = l; i <= r; ++i) {
    if (a[i] != b[r - (i - l)]) {
      cout << "impossible" << endl;
      exit(0);
    }
  }
  cout << l + 1 << ' ' << r + 1 << endl;
}
