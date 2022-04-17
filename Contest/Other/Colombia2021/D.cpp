#include <bits/stdc++.h>
using namespace std;

pair<int, string_view> ParseExponent(string_view s) {
  if (s[0] == '^') {
    if (s[1] == '-') {
      int x = 0, p = 2;
      while (p < s.size() && isdigit(s[p])) {
        x = x * 10 + (s[p] - '0');
        p++;
      }
      return make_pair(-x, s.substr(p));
    }
    int x = 0, p = 1;
    while (p < s.size() && isdigit(s[p])) {
      x = x * 10 + (s[p] - '0');
      p++;
    }
    return make_pair(x, s.substr(p));
  }
  return make_pair(0, s);
}

pair<pair<int, int>, string_view> ParseTerm(string_view s) {
  if (s[0] == 'x') {
    auto [e, t] = ParseExponent(s.substr(1));
    if (e == 0) e = 1;
    return make_pair(make_pair(e, 1), t);
  } else {
    int p = 0, x = 0;
    while (p < s.size() && isdigit(s[p])) {
      x = x * 10 + (s[p] - '0');
      p++;
    }
    if (s[p] != 'x') {
      return make_pair(make_pair(0, x), s.substr(p));
    }
    assert(s[p] == 'x');
    p++;
    auto [e, t] = ParseExponent(s.substr(p));
    // cout << "x = " << x << " e = " << e << " t = " << t << endl;
    if (e == 0) e = 1;
    return make_pair(make_pair(e, x), t);
  }
}

vector<pair<int, int>> ParsePoly(string_view s) {
  if (s == "0") {
    return {{0, 0}};
  }
  vector<pair<int, int>> res;
  while (!s.empty()) {
    int cf = 1;
    if (s[0] == '+') {
      cf = 1;
      s = s.substr(1);
    } else if (s[0] == '-') {
      cf = -1;
      s = s.substr(1);
    }
    auto [p, t] = ParseTerm(s);
    res.emplace_back(p.first, p.second * cf);
    s = t;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  auto poly = ParsePoly(s);
  // for (auto [e, c] : poly) {
  //   cout << e << " " << c << endl;
  // }
  sort(poly.begin(), poly.end());
  vector<pair<int, int>> ans;
  for (int i = 0, j = 0; i < poly.size(); i = j) {
    int sum = 0;
    while (j < poly.size() && poly[j].first == poly[i].first) {
      sum += poly[j].second;
      j++;
    }
    ans.emplace_back(poly[i].first == 0 ? 0 : poly[i].first - 1, poly[i].first * sum);
  }
  sort(ans.begin(), ans.end());
  vector<pair<int, int>> fin;
  for (int i = 0, j = 0; i < ans.size(); i = j) {
    int sum = 0;
    while (j < ans.size() && ans[j].first == ans[i].first) {
      sum += ans[j].second;
      j++;
    }
    fin.emplace_back(ans[i].first, sum);
  }
  // cout << "fin" << endl;
  // for (auto [e, t] : fin) {
  //   cout << e << " " << t << endl;
  // }
  bool ppp = false;
  for (int i = 0; i < fin.size(); ++i) {
    auto t = fin[i];
    if (t.second == 0) {
      continue;
    }
    if (t.first != 0) {
      if (abs(t.second) == 1) {
        if (t.second == -1) cout << "-";
        else if (ppp) cout << "+";
      } else {
        if (t.second > 0 && ppp) cout << "+";
        cout << t.second;
      }
      cout << "x";
      if (t.first != 1) {
        cout << "^";
        cout << t.first;
      }
    } else {
      if (t.second > 0 && ppp) cout << "+";
      cout << t.second;
    }
    ppp = true;
  }
  if (!ppp) {
    cout << "0";
  }
  cout << "\n";
  return 0;
}
