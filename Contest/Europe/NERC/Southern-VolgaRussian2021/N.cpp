#include <bits/stdc++.h>
using namespace std;


int main() {
  int t; cin >> t; while (t--) {
    int cnt[3] = {0};

    for (int i = 0; i < 3; ++i) cin >> cnt[i];

    int ok = 1;
    for (int i = 0; i < 3; ++i) {
      int x = 0, y = 0;
      for (int j = 0; j < cnt[i]; ++j) {
        string s; cin >> s;
        for (char c : s) {
          if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';

          if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            ++x;
          else if (c == 'y')
            ++y;
        }
      }

      if (i == 0 || i == 2) {
        if (x <= 5 && 5 <= x + y);
        else ok = 0;
      } else {
        if (x <= 7 && 7 <= x + y);
        else ok = 0;
      }
    }

    if (ok) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
}

