#include <bits/stdc++.h>
using namespace std;

string st[2555];

int main() {
  int n; cin >> n;
  cin >> st[0];
  for (int i = 1; i < n; ++i) {
    string s; cin >> s;
    if (s == "SUB") {
      int x, l, r; cin >> x >> l >> r;
      st[i] = st[x].substr(l, r - l);
    } else {
      int a, b; cin >> a >> b;
      st[i] = st[a] + st[b];
    }
  }

  long long ans = 0;
  for (char c : st[n - 1]) ans += c;
  cout << ans << endl;
}
