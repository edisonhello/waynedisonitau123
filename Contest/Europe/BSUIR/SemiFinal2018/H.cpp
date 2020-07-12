#include <bits/stdc++.h>
using namespace std;

int64_t Solve(string s) {
  int64_t res = 0;
  vector<int64_t> pw(1, 1);
  while (pw.back() * 5 <= 1'000'000'000'000'000'000) {
    pw.push_back(pw.back() * 5);
  }
  for (int i = 0; i < s.size(); ++i) {
    int d = s[i] - '0';
    for (int j = 0; j < d; ++j) {
      if (j == 1 || j == 2 || j == 3 || j == 5 || j == 8) continue;
      res += pw[s.size() - 1 - i];
    }
    if (d == 1 || d == 2 || d == 3 || d == 5 || d == 8) break;
  }
  bool ok = true;
  for (char c : s) ok &= c != '1' && c != '2' && c != '3' && c != '5' && c != '8';
  if (ok) res++;
  return res;
}

int main() {
  vector<int64_t> f = {1, 1};
  while (true) {
    int64_t x = f[f.size() - 2] + f[f.size() - 1];
    if (x > 1'000'000'000'000'000'000) break;
    int64_t v = x;
    bool ok = false;
    while (v > 0) {
      int d = v % 10;
      ok |= d == 1 || d == 2 || d == 3 || d == 5 || d == 8;
      v /= 10;
    }
    assert(ok);
    f.push_back(x);
  }
  int t;
  cin >> t;
  while (t--) {
    string n;
    cin >> n;
    cout << Solve(n) << "\n";
  }
}
