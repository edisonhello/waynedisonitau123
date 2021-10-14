#include <bits/stdc++.h>
using namespace std;

pair<int, string_view> ParseY(string_view s);

pair<int, string_view> ParseX(string_view s) {
  auto [y, t] = ParseY(s); 
  if (t.empty() || t[0] != '-') {
    return make_pair(y, t);
  }
  assert(t[0] == '-');
  assert(t[1] == '>');
  t = t.substr(2);
  auto [x, r] = ParseX(t);
  return make_pair(max(y + 1, x), r);
}

pair<int, string_view> ParseY(string_view s) {
  if (s.empty() || s[0] != '(') {
    return make_pair(0, s);
  }
  assert(s[0] == '(');
  auto [x, t] = ParseX(s.substr(1));
  assert(t[0] == ')');
  return make_pair(x, t.substr(1));
}

int main() {
  string s;
  cin >> s;
  cout << ParseX(s).first << endl;
}
