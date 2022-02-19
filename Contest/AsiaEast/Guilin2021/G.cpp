#include <bits/stdc++.h>
using namespace std;


int main() {
  int t; cin >> t; while (t--) {
    int n; cin >> n;
    string s; cin >> s;

    bool all_one = 1;
    for (char c : s) if (c == '0') all_one = 0;
    if (all_one) {
      cout << 0 << '\n';
      continue;
    }

    auto win = [&](int step) -> bool {
      // cout << "step " << step << endl;
      int left1 = 0;
      int leftr = 0;
      int cnt0 = 0;
      for (int i = 0; i < n; ++i) {
        char c = s[i];
        
        if (c == '0') ++cnt0;
        else if (c == '1') {
          if (!left1) {
            if (cnt0 > step) return false;
            if (cnt0 == step) {
              left1 = 1;
              leftr = 0;
            } else {
              left1 = 1;
              leftr = 1;
            }
          } else {
            if (!leftr) {
              if (cnt0 > (step - 1) + step) return false;
              if (cnt0 == (step - 1) + step) {
                left1 = 1;
                leftr = 0;
              } else {
                left1 = leftr = 1;
              }
            } else {
              if (cnt0 > step + step) return false;
              if (cnt0 == step + step) {
                left1 = 1;
                leftr = 0;
              } else {
                left1 = leftr = 1;
              }
            }
          }
          cnt0 = 0;
        }
      }

      // cout << "last leftr cnt0 " << leftr << ' ' << cnt0 << endl;
      if (!leftr) {
        if (cnt0 > step - 1) return 0;
      } else {
        if (cnt0 > step) return 0;
      }

      return 1;
    };

    int L = 1, R = n;
    while (L < R) {
      int M = (L + R) >> 1;
      if (win(M)) R = M;
      else L = M + 1;
    }
    cout << L << '\n';
  }
}

