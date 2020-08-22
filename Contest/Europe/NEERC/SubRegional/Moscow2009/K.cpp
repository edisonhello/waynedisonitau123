#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("kaleidoscope.in", "r", stdin);
  freopen("kaleidoscope.out", "w", stdout);

  int n, k; cin >> n >> k;
  vector<pair<int, string>> v(n);
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    int sum = 0;
    for (char c : s) {
      if (c >= '0' && c <= '9') sum += c - '0';
    }
    v[i] = make_pair(sum, s);
  }

  while (k > 2) {
    cout << v.back().second << '\n';
    v.pop_back();
    --k;
  }


  int tp = 0;
  for (auto &p : v) tp += p.first & 1;
  if (tp == 0 || tp == v.size()) {
    cout << v.back().second << '\n';
    v.pop_back();
    for (auto &p : v) cout << p.second << ' ';
    cout << '\n';
  } else {
    for (auto &p : v) if (p.first & 1) cout << p.second << ' ';
    cout << '\n';
    for (auto &p : v) if (!(p.first & 1)) cout << p.second << ' ';
    cout << '\n';
  }
}
