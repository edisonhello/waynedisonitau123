#include <bits/stdc++.h>
using namespace std;

int dp[400005][27];

set<int> parse(string s) {
  set<int> ret;
  sort(s.begin(), s.end());
  do {
    int z = 0;
    for (char c : s) z = z * 3 + (c == 'Q' ? 0 : c == 'W' ? 1 : 2);
    ret.insert(z);
  } while (next_permutation(s.begin(), s.end()));
  return ret;
}

set<int>& skill(char c) {
  static vector<set<int>> rec(128);
  if (rec[c].size()) return rec[c];
  if (c == 'Y') return rec[c] = parse("QQQ");
  if (c == 'V') return rec[c] = parse("QQW");
  if (c == 'G') return rec[c] = parse("QQE");
  if (c == 'C') return rec[c] = parse("WWW");
  if (c == 'X') return rec[c] = parse("QWW");
  if (c == 'Z') return rec[c] = parse("WWE");
  if (c == 'T') return rec[c] = parse("EEE");
  if (c == 'F') return rec[c] = parse("QEE");
  if (c == 'D') return rec[c] = parse("WEE");
  if (c == 'B') return rec[c] = parse("QWE");
  assert(false);
}

void Update(int &x, int y) { x = max(x, y); }

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  string s; cin >> s;
  int n = s.size();

  if (n == 1) {
    cout << 4 << endl;
    exit(0);
  }

  // memset(dp, 0xb0, sizeof(dp));

  for (int z : skill(s[0])) dp[4][z] = 1;
  for (int i = 5; i <= n * 4; ++i) {
    for (int y = 0; y < 27; ++y) {
      int nidx = dp[i - 1][y];
      auto &st = skill(s[nidx]);

      // cerr << "i y st " << i << ' ' << y << ' ';
      // for (int i : st) cerr << i << ' ';
      // cerr << endl;

      if (st.count(y)) {
        // cerr << "at i = " << i << " y = " << y << " nidx update" << endl;
        Update(dp[i][y], nidx + 1);
      }

      for (int z = 0; z < 3; ++z) {
        int zz = (y * 3 + z) % 27;
        Update(dp[i][zz], nidx);
      }
    }

    for (int z = 0; z < 27; ++z) {
      if (dp[i][z] == n) {
        cout << i << endl;
        exit(0);
      }
      // cerr << "dp " << i << ' ' << z << ' ' << dp[i][z] << endl;
    }
  }


}
