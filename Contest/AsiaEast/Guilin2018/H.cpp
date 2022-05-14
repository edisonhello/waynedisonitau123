#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    string a, b;
    cin >> a >> b;
    int N = a.size();
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
      cnt += (a[i] == b[i]);
    }
    string ans = "";
    int offset = 0;
    for (int i = 0; i < N; ++i) {
      cnt -= (a[i] == b[i]);
      if (a[i] == b[i]) {
        ans += "a"; 
      } else {
        int diff = (N - i - 1) - cnt;
        for (char c = 'a'; c <= 'z'; ++c) {
          if (a[i] == c) {
            if (abs(offset + 1) <= diff) {
              ans += c;
              offset++;
              break;
            }
          } else if (b[i] == c) {
            if (abs(offset - 1) <= diff) {
              ans += c;
              offset--;
              break;
            }
          } else {
            if (abs(offset) <= diff) {
              ans += c;
              break;
            }
          }
        }
      }
    }
    cout << "Case " << tc << ": " << ans << "\n";
  }
  return 0;
}
