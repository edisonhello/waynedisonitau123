#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t; while (t--) {
    string s, t; cin >> s >> t;
    vector<int> cs(3, 0);
    vector<int> ct(3, 0);
    for (char c : s) {
      cs[c - 'A']++;
    }
    for (char c : t) {
      ct[c - 'A']++;
    }

    int same = 1;
    for (int i = 0; i < 3; ++i) {
      same &= (cs[i] % 2 == ct[i] % 2);
    }

    if (!same) {
      cout << "NO" << '\n';
      continue;
    }

    string ss, tt;
    for (char c : s) {
      if (c == 'B') continue;
      if (ss.size() && c == ss.back()) ss.pop_back();
      else ss += c;
    }

    for (char c : t) {
      if (c == 'B') continue;
      if (tt.size() && c == tt.back()) tt.pop_back();
      else tt += c;
    }

    if (ss == tt) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }

}

