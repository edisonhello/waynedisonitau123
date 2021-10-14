#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  vector<int> cnt(256);
  for (int i = 0; i < s.size(); ++i) {
    cnt[s[i]]++;
  }
  constexpr int kP = 1'000'000'000 + 7;
  int ans = 1;
  for (char c : "BSUIROPEN") {
    if (c == 0) break;
    ans = 1LL * ans * cnt[c] % kP;
  }
  cout << ans << "\n";
}
