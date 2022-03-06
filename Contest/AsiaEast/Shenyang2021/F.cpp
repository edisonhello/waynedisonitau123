#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  string ans = "";

  auto Encode = [&](const string& s) {
    vector<bool> vis(26);
    vector<char> to(26);
    int cnt = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
      if (!vis[s[i] - 'a']) {
        to[s[i] - 'a'] = 'a' + cnt;
        cnt++;
        vis[s[i] - 'a'] = true;
      }
    }
    string t = s;
    for (int i = 0; i < t.size(); ++i) {
      t[i] = to[t[i] - 'a'];
    }
    return t;
  };

  for (int i = 1; i <= n; ++i) {
    string t = Encode(s.substr(0, i));
    ans = max(ans, t);
  }
  cout << ans << "\n";
  return 0;
}

