#include <bits/stdc++.h>
using namespace std;

vector<int> Failure(const string& s) {
  vector<int> f(s.size(), 0);
  int k = 0;
  for (int i = 1; i < s.size(); ++i) {
    while (k > 0 && s[i] != s[k]) {
      k = f[k - 1];
    }
    if (s[i] == s[k]) {
      k++;
    }
    f[i] = k;
  }
  return f;
}

int main() {
  string s;
  while (cin >> s) {
    int64_t ans = 0;
    for (int i = 0; i < s.size(); ++i) {
      vector<int> f = Failure(s.substr(i));
      ans += accumulate(f.begin(), f.end(), 0);
    }
    cout << ans << "\n";
  }
}
