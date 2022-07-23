#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, T;
  cin >> N >> T;
  string s;
  cin >> s;

  auto Win = [&](char a, char b) {
    if (a == b) {
      return true;
    }
    if (a == 'R') {
      return b == 'S';
    }
    if (a == 'P') {
      return b == 'R';
    }
    if (a == 'S') {
      return b == 'P';
    }
  };

  string ans = "";
  for (int i = 0, j = 0; i < N; i = j) {
    int cnt = 0;
    while (j < N && Win(s[i], s[j])) {
      cnt += (s[j] == s[i]);
      j++;
    }
    int p = min(T, cnt);
    int q = p;
    string ns = "";
    char c = s[i];
    for (int k = i; k < j; ++k) {
      if (s[k] == c && p > 0) {
        p--;
        continue;
      }
      ns += s[k];
    }
    ns += string(q, c);
    ans += ns;
  }
  cout << ans << "\n";
}
