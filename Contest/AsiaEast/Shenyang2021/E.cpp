#include <bits/stdc++.h>
using namespace std;

int main() {
  string s; cin >> s;

  int n = s.size();
  int cnt = 0;
  for (int i = 4; i < n; ++i) {
    if (s[i - 4] == 'e' && s[i - 3] == 'd' &&  s[i - 2] == 'g' && s[i - 1] == 'n' && s[i] == 'b') ++cnt;
  }

  cout << cnt << endl;
}

