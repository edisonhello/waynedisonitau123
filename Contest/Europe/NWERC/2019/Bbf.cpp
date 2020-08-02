#include <bits/stdc++.h>
using namespace std;

int p[500005];
int l[500005], r[500005];
int dep[500005];

bool dfs(int now, int z) {
  // cerr << "dfs now z " << now << ' ' << z << endl;
  int lc = l[now], rc = r[now];
  if (lc && !(z & (1 << (lc - 1)))) lc = 0;
  if (rc && !(z & (1 << (rc - 1)))) rc = 0;

  if (!lc && !rc) {
    dep[now] = 0;
    return 1;
  }

  if (lc && !dfs(lc, z)) return 0;
  if (rc && !dfs(rc, z)) return 0;

  // cerr << "z now = " << z << ' ' << now << " lc " << lc << ' ' << "rc " << rc << " deps " << dep[lc] << ' ' << dep[rc] << endl;

  if (!lc && dep[rc] > 0) return 0;
  if (!rc && dep[lc] > 0) return 0;
  if (abs(dep[lc] - dep[rc]) > 1) return 0;

  dep[now] = max(dep[lc], dep[rc]) + 1;
  return 1;
}

int main() {
  int n, k; cin >> n >> k;
  int root = 0;

  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    if (p[i] == -1) root = i;
    else {
      if (p[i] < i) r[p[i]] = i;
      else l[p[i]] = i;
    }
  }

  string ans = "";
  for (int z = 1; z < (1 << n); ++z) if (__builtin_popcount(z) == k) {
    bool ok = 1;
    for (int i = 1; i <= n; ++i) if (z & (1 << (i - 1))) {
      if (p[i] == -1) continue;
      if (!(z & (1 << (p[i] - 1)))) ok = 0;
    }
    if (!(z & (1 << (root - 1)))) ok = 0;

    if (!ok) continue;

    if (!dfs(root, z)) ok = 0;
    
    if (!ok) continue;

    string tmp;
    for (int i = 1; i <= n; ++i) 
      if (z & (1 << (i - 1))) tmp += "1";
      else tmp += "0";

    // cerr << "tmp = " << tmp << endl;

    ans = max(tmp, ans);
  }

  cout << ans << endl;
}
