#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  const string kS = "BSUIROPENX";
  vector<int> p(kS.size() + 1), q(kS.size() + 1);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (s.size() > kS.size()) continue;
    if (kS.substr(0, s.size()) == s) p[s.size()]++;
    if (kS.substr(kS.size() - s.size()) == s) q[s.size()]++;
  }
  int64_t res = 0;
  for (int i = 1; i < kS.size(); ++i) {
    res += 1LL * p[i] * q[kS.size() - i];
  }
  cout << res << "\n";
}
