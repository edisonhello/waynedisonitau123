#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

pii operator- (const pii &a, const pii &b) {
  return pii(a.first - b.first, a.second - b.second);
}
long long operator^ (const pii a, const pii b) {
  return a.first * 1ll * b.second - a.second * 1ll * b.first;
}

bool inside(pii x, pii p1, pii p2, pii p3) {
  if (abs((p2 - p1) ^ (p3 - p1)) == (abs((p1 - x) ^ (p2 - x)) + abs((p2 - x) ^ (p3 - x)) + abs((p3 - x) ^ (p1 - x))))
    return true;
  return false;
}

bool tu(pii p1, pii p2, pii p3, pii p4) {
  if (inside(p1, p2, p3, p4)) return 0;
  if (inside(p2, p3, p4, p1)) return 0;
  if (inside(p3, p4, p1, p2)) return 0;
  if (inside(p4, p1, p2, p3)) return 0;
  return 1;
}

int main() {
  int n; cin >> n;
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;

  int out = 0;
  for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) for (int k = j + 1; k < n; ++k) for (int l = k + 1; l < n; ++l) {
    if (tu(v[i], v[j], v[k], v[l])) ++out;
  }

  cout << fixed << setprecision(12);
  cout << (double)((out * 2 + 1ll * n * (n - 1) * (n - 2) * (n - 3) / 24 - out)) / (1ll * n * (n - 1) * (n - 2) / 6) << endl;
}
