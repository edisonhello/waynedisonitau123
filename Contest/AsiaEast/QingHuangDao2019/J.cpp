#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int A, B;
  cin >> A >> B;
  string s;
  cin >> s;
  int p = find(s.begin(), s.end(), '.') - s.begin();
  s = s.substr(p + 1);
  reverse(s.begin(), s.end());
  int N = s.size();
  vector<int> f(N);
  int k = 0;
  for (int i = 1; i < N; ++i) {
    while (k > 0 && s[i] != s[k]) k = f[k - 1];
    if (s[i] == s[k]) k++;
    f[i] = k;
  }
  int64_t ans = -1'000'000'000'000'000'000;
  for (int i = 0; i < N; ++i) {
    int t = i + 1 - f[i];
    ans = max<int64_t>(ans, 1LL * A * (i + 1) - 1LL * B * t);
  }
  cout << ans << "\n";
}
