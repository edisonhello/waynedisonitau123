#include <bits/stdc++.h>
using namespace std;

int check(string &s, string &ss) {
  if (s.size() != ss.size()) return false;

  int ux = -1;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (s[i] >= '0' && s[i] <= '9') {
      if (ss[i] != s[i]) return false;
    } else if (s[i] == 'X') {
      if (ux == -1) ux = ss[i];
      else if (ux != ss[i]) return false;
    }
  }
  return true;
}

int main() {
  string s; cin >> s;

  int cnt = 0;
  for (int i = 0; i < 1000000; ++i) {
    for (int j = 0; j < 100; j += 25) {
      int x = i * 100 + j;
      stringstream ss;
      ss << x;
      string sss;
      ss >> sss;
      if (check(s, sss)) ++cnt;
    }
  }
  cout << cnt << endl;

}
