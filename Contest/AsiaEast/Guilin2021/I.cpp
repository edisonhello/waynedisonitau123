#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) {
    int n; cin >> n;
    string s; cin >> s;

    int trash = 0;
    int64_t sum = 0;
    for (int i = n - 1; i >= 0; --i) {
      if (s[i] == '1') {
        if (trash) {
          --trash;
          sum += i + 1;
        } else ++trash;
      } else ++trash;
    }

    cout << sum << '\n';
  }
}

