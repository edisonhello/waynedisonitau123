#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string s;
  cin >> s;
  int pos = s.find('=');
  assert(pos != string::npos);
  string lhs = s.substr(0, pos);
  string rhs = s.substr(pos + 1);
  vector<int> var(26);
  vector<int> lc(10), rc(10);
  for (int i = 0; i < lhs.size(); ++i) {
    if (i & 1) {
      assert(lhs[i] == '*');
    } else {
      if (isdigit(lhs[i])) {
        int v = lhs[i] - '0';
        for (int p = 2; p <= v; ++p) {
          while (v % p == 0) {
            lc[p]++;
            v /= p;
          }
        }
      } else {
        assert(islower(lhs[i]));
        var[lhs[i] - 'a']++;
      }
    }
  }
  for (int i = 0; i < rhs.size(); ++i) {
    if (i & 1) {
      assert(rhs[i] == '*');
    } else {
      assert(isdigit(rhs[i]));
      int v = rhs[i] - '0';
      for (int p = 2; p <= v; ++p) {
        while (v % p == 0) {
          rc[p]++;
          v /= p;
        }
      }
    }
  }
  for (int i = 0; i < 10; ++i) {
    if (lc[i] > rc[i]) {
      cout << "0\n";
      return 0;
    }
  }
  constexpr int kP = 1'000'000'000 + 7;
  int ans = 1;
  for (int i = 0; i < 10; ++i) {
    int diff = rc[i] - lc[i];
    vector<int> dp(diff + 1);
    dp[0] = 1;
    for (int c = 0; c < 26; ++c) {
      if (var[c] == 0) continue;
      vector<int> nxt(diff + 1);
      for (int t = 0; t * var[c] <= diff; ++t) {
        for (int j = 0; j + t * var[c] <= diff; ++j) {
          (nxt[j + t * var[c]] += dp[j]) %= kP;
        }
      }
      dp = nxt;
    }
    ans = 1LL * ans * dp[diff] % kP;
  }
  cout << ans << "\n";
  return 0;
}
