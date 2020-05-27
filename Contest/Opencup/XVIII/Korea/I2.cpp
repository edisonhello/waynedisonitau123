#include <bits/stdc++.h>
using namespace std;

struct SuffixAut {
  vector<vector<int>> nxt;
  vector<int64_t> dp;
  vector<int> to, len, pv;
  int root, last;
  int64_t ans;

  int Get(int x, int64_t d) {
    int res = nxt.size();
    nxt.emplace_back(26, -1);
    to.push_back(-1);
    len.push_back(x);
    dp.push_back(d);
    pv.push_back(1);
    ans += d;
    return res;
  }

  SuffixAut() : root(Get(0, 1)), last(root), ans(1) {}

  void Push(int c) {
    int cur = last;
    last = Get(len[last] + 1, 0);
    for (; ~cur && nxt[cur][c] == -1; cur = to[cur]) {
      nxt[cur][c] = last;
      ans += dp[cur] * pv[last] * pv[last];
      dp[last] += dp[cur];
    }
    if (cur == -1) {
      to[last] = root;
    } else {
      int link = nxt[cur][c];
      if (len[link] == len[cur] + 1) {
        to[last] = link;
      } else {
        int tlink = Get(len[cur] + 1, dp[cur]);
        for (; ~cur && nxt[cur][c] == link; cur = to[cur]) {
          dp[tlink] += dp[cur];
          ans += dp[cur] * pv[tlink] * pv[tlink];
          nxt[cur][c] = tlink;
          dp[link] -= dp[cur];
          ans -= dp[cur] * pv[link] * pv[link];
        }
        for (int i = 0; i < 26; ++i) {
          nxt[tlink][i] = nxt[link][i];
          if (nxt[tlink][i] != -1) {
            dp[nxt[tlink][i]] += dp[tlink];
            ans += dp[tlink] * pv[nxt[tlink][i]] * pv[nxt[tlink][i]];
          }
        }
        to[tlink] = to[link];
        to[link] = tlink;
        to[last] = tlink;
      }
    }
    int g = last;
    while (~to[g]) {
      ans -= pv[to[g]] * pv[to[g]] * dp[to[g]];
      pv[to[g]]++;
      ans += pv[to[g]] * pv[to[g]] * dp[to[g]];
      g = to[g];
    }
  }
};

int main() {
  string s;
  cin >> s;
  SuffixAut aut;
  for (int i = 0; i < s.size(); ++i) {
    aut.Push(s[i] - 'a');
    for (int j = 0; j < aut.nxt.size(); ++j) {
      cout << j << ": (";
      for (int k = 0; k < 26; ++k) {
        if (aut.nxt[j][k] != -1) cout << (char)(k + 'a') << ": " << aut.nxt[j][k] << ", ";
      }
      cout << "), ";
      cout << aut.to[j] << " " << aut.dp[j] << " " << aut.pv[j] << "\n";
    }
    cout << aut.ans - 1LL * aut.pv[0] * aut.pv[0]  << "\n";
  }
}
