#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  auto Solve = [&](string s) {
    map<string, int> cnt;
    for (int i = 0; i < s.size(); ++i) {
      string t = "";
      for (int j = i; j < s.size(); ++j) {
        t += s[j];
        cnt[t]++;
      }
    }
    int res = 0;
    for (auto it : cnt) res += it.second * it.second;
    return res;
  };

  for (int i = 0; i < s.size(); ++i) {
    cout << Solve(s.substr(0, i + 1)) << "\n";
  }
}
