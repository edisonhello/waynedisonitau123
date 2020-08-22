#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("agnatic.in", "r", stdin);
  freopen("agnatic.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<string> s(n);
  vector<int> gc(26);
  vector<vector<int>> gr(26);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
    vector<int> cnt(26);
    for (int j = 0; j < s[i].size(); ++j) {
      cnt[s[i][j] - 'A']++;
    }
    for (int j = 0; j < 26; ++j) {
      if (cnt[j] > 0) {
        if (gc[j] != 0 && gc[j] != cnt[j]) {
          cout << "NO\n";
          return 0;
        }
        gc[j] = cnt[j];
        gr[j].push_back(i);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    reverse(s[i].begin(), s[i].end());
  }
  vector<int> hd(26);
  for (int i = 0; i < n; ++i) {
    hd[s[i].back() - 'A']++; 
  }
  int sum = accumulate(gc.begin(), gc.end(), 0);
  string res = "";
  for (int i = 0; i < sum; ++i) {
    bool ok = false;
    for (int j = 0; j < 26; ++j) {
      if (gc[j] == 0) continue;
      if (hd[j] == gr[j].size()) {
        res += j + 'A';
        hd[j] = 0;
        for (int u : gr[j]) {
          assert(!s[u].empty());
          s[u].pop_back();
          if (!s[u].empty()) {
            hd[s[u].back() - 'A']++;
          }
        }
        gc[j]--;
        ok = true;
        break;
      }
    }
    if (!ok) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  cout << res << "\n";
}
