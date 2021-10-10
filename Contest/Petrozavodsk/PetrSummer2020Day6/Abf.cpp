#include <bits/stdc++.h>
using namespace std;

string gen(string m, string r) {
  string ans;
  for (char c : r) {
    if (c == '$') ans += m;
    else ans += c;
  }
  return ans;
}

int main() {
  string m, r; cin >> m >> r;
  int k, q; cin >> k >> q;

  while (k--) {
    m = gen(m, r);
  }

  while (q--) {
    int l, r; cin >> l >> r;
    for (int i = l - 1; i <= r - 1; ++i) cout << m[i];
    cout << endl;
  }
}
