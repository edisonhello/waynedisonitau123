#include <bits/stdc++.h>
using namespace std;

map<vector<int>, int> dp;

int dfs(vector<int> a) {
  auto it = dp.find(a);
  if (it != dp.end()) return it->second;

  if (a.size() == 1u) return 0;
  
  vector<int> b = a;
  --b[0];
  if (b[0] == 1) b.erase(b.begin());
  if (dfs(b) == 0) return dp[a] = 1;

  b = a;
  --b.back();
  if (b.back() == 1) b.pop_back();
  if (dfs(b) == 0) return dp[a] = 1;

  return dp[a] = 0;
}


int main() {
  // int n; cin >> n;
  // vector<int> v(n);
  // for (int i = 0; i < n; ++i) cin >> v[i];

  // cout << dfs(v) << endl;

  // for (int a = 2; a <= 10; ++a) for (int b = 2; b <= 10; ++b) cerr << a << ' ' << b << ' ' << dfs(vector<int>{a, b}) << endl;
  for (int a = 2; a <= 10; ++a) for (int b = 2; b <= 10; ++b) for (int c = 2; c <= 10; ++c) for (int d = 2; d <= 10; ++d) {
    if (a != 2 && b != 2 && c != 2 && d != 2 && (a + b + c + d - 3) % 2 == 1) {
      if (dfs(vector<int>{a, b, c, d})) {
        cerr << a << ' ' << b << ' ' << c << ' ' << d << endl;
      }
    }
  }
}
