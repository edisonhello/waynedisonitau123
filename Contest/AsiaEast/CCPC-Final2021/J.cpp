#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

namespace std {

template <>
struct hash<vector<int8_t>> {
  uint64_t operator()(const vector<int8_t>& v) const {
    uint64_t res = 0;
    for (int i = 0; i < v.size(); ++i) {
      res = res * 10 + v[i];
    }
    return res;
  }
};

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<string> s(N);
    vector<int8_t> score(N);
    for (int i = 0; i < N; ++i) {
      int x;
      cin >> s[i] >> x;
      score[i] = x / 10;
    }
    unordered_map<vector<int8_t>, int> vec;
    for (int t = 0; t < (1 << 10); ++t) {
      int g = t;
      vector<int8_t> v = score;
      bool ok = true;
      for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < N; ++i) {
          v[i] -= (s[i][j] - 'A') == (g % 4);
          if (v[i] < 0) {
            ok = false;
          }
        }
        g /= 4;
      }
      if (ok) {
        vec[v]++;
      }
    }
    // sort(vec.begin(), vec.end());
    int ans = 0;
    for (int t = 0; t < (1 << 10); ++t) {
      int g = t;
      vector<int8_t> v(N, 0);
      for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < N; ++i) {
          v[i] += (s[i][j + 5] - 'A') == (g % 4);
        }
        g /= 4;
      }
      if (vec.find(v) != vec.end()) {
        ans += vec[v];
      }
      // ans += upper_bound(vec.begin(), vec.end(), v) -
      //        lower_bound(vec.begin(), vec.end(), v);
    }
    cout << ans << "\n";
  }
}
