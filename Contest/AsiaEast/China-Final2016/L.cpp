#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<pair<int, int>> kM = {
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 2},
    {1, 3},
    {2, 3}
  };
  map<vector<int>, int> cnt;
  for (int s = 0; s < 729; ++s) {
    int v = s;
    vector<int> score(4);
    for (int i = 0; i < 6; ++i) {
      int d = v % 3;
      v /= 3;
      if (d == 0) score[kM[i].first] += 3;
      if (d == 1) score[kM[i].second] += 3;
      if (d == 2) score[kM[i].first]++, score[kM[i].second]++;
    }
    cnt[score]++;
  }
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    cout << "Case #" << i + 1 << ": ";
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    vector<int> v = {A, B, C, D};
    if (cnt.find(v) == cnt.end()) cout << "Wrong Scoreboard\n";
    else if (cnt[v] == 1) cout << "Yes\n";
    else cout << "No\n";
  }
}
