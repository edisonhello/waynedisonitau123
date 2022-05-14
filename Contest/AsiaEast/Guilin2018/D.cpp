#include <bits/stdc++.h>
using namespace std;

int solve(string now, string to) {
  assert(now.size() == to.size());
  int n = now.size();

  int sum = 0;
  for (int i = 0; i < n; ++i) {
    if (now[i] == to[i]) continue;
    int j = i + 1;
    while (j < n and now[j] != to[i]) ++j;
    if (j == n) return -1;

    swap(now[i], now[j]);
    sum += (j - i);
  }

  return sum;
}

void solve() {
  int64_t x, y;
  cin >> x >> y;

  string now, to;
  for (int i = 0; i < 60; i += 2) {
    now += (char)('0' + !!(x & (1ll << i)));
    to += (char)('0' + !!(y & (1ll << i)));
  }

  int a1 = solve(now, to);

  now = to = "";
  for (int i = 1; i < 60; i += 2) {
    now += (char)('0' + !!(x & (1ll << i)));
    to += (char)('0' + !!(y & (1ll << i)));
  }

  int a2 = solve(now, to);

  if (a1 == -1 or a2 == -1) {
    cout << -1 << '\n';
    return;
  }

  cout << a1 + a2 << '\n';
}

int main() {
  int t; cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case " << T << ": ";
    solve();
  }
}

