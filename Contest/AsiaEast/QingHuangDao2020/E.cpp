#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N, p;
    cin >> N >> p;
    vector<int> a(N), b(N);
    vector<pair<int, int>> vec;
    int B = 0;
    for (int i = 0; i < N; ++i) {
      cin >> a[i] >> b[i];
      vec.emplace_back(a[i], i);
      vec.emplace_back(b[i], i);
      B = max(B, b[i]);
    }
    sort(vec.begin(), vec.end());
    vector<int> cnt(N);
    int res = 0, ans = 0;
    for (int i = 0, j = 0; i < vec.size(); ++i) {
      while (j < i && vec[j].first * 100LL < 1LL * vec[i].first * p) {
        if (--cnt[vec[j].second] == 0) {
          res--;
        }
        j++;
      }
      if (cnt[vec[i].second]++ == 0) {
        res++;
      }
      if (vec[i].first >= B) {
        ans = max(ans, res);
      }
    }
    cout << "Case #" << tc << ": " << ans << "\n";
  }
}

