#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) {
    int n; char targ; cin >> n >> targ;
    string s, t; cin >> s >> t;

    if (s >= t) {
      cout << "NO" << '\n';
      continue;
    }

    auto dfs = [&] (auto dfs, int idx, int lb, int ub, bool occur, string &cur) -> string {
      if (idx == n) {
        if (lb || ub) return "";
        if (!occur) return "";
        return cur;
      }

      for (char c = 'a'; c <= 'z'; ++c) {
        if (lb && c < s[idx]) continue;
        if (ub && c > t[idx]) continue;
        cur += c;
        string ans = dfs(dfs, idx + 1, lb & (c == s[idx]), ub & (c == t[idx]), occur | (c == targ), cur);
        if (ans.size()) return ans;
        cur.pop_back();
      }

      return "";
    };

    string cur = "";
    cur = dfs(dfs, 0, 1, 1, false, cur);

    if (cur.size()) 
      cout << cur << '\n';
    else cout << "NO" << '\n';
  }
}
