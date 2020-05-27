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

  void SetDP(int x, int d) {
    if (x == -1) return;
    ans -= dp[x] * pv[x] * pv[x];
    dp[x] = d;
    ans += dp[x] * pv[x] * pv[x];
  }

  void SetPV(int x, int d) {
    if (x == -1) return;
    ans -= dp[x] * pv[x] * pv[x];
    pv[x] = d;
    ans += dp[x] * pv[x] * pv[x];
  }

  void SetLink(int x, int t) {
    if (x == -1) return;
    for (int y = to[x]; y >= 0; y = to[y]) SetPV(y, pv[y] - 1);
    to[x] = t;
    for (int y = to[x]; y >= 0; y = to[y]) SetPV(y, pv[y] + 1);
  }

  void SetNxt(int x, int y, int z) {
    if (nxt[x][y] != -1) {
      SetDP(nxt[x][y], dp[nxt[x][y]] - dp[x]);
    }
    nxt[x][y] = z;
    SetDP(nxt[x][y], dp[nxt[x][y]] + dp[x]);
  }

  SuffixAut() : root(Get(0, 1)), last(root), ans(1) {}

  void Push(int c) {
    int cur = last;
    last = Get(len[last] + 1, 0);
    for (; ~cur && nxt[cur][c] == -1; cur = to[cur]) {
      SetNxt(cur, c, last);
    }
    if (cur == -1) {
      SetLink(last, root);
      return;
    }
    int link = nxt[cur][c];
    if (len[link] == len[cur] + 1) {
      SetLink(last, link);
      return;
    }
    int tlink = Get(len[cur] + 1, 0);
    for (; ~cur && nxt[cur][c] == link; cur = to[cur]) {
      SetNxt(cur, c, tlink);
    }
    for (int i = 0; i < 26; ++i) {
      SetNxt(tlink, i, nxt[link][i]);
    }
    SetLink(tlink, to[link]);
    SetLink(link, tlink);
    SetLink(last, tlink);
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
