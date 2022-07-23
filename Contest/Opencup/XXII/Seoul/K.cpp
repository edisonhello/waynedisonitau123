#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  int64_t sum = 0;
  for (int it = 0; it < N; ++it) {
    int H, W;
    cin >> H >> W;
    string s, t;
    cin >> s >> t;
    vector<pair<int, int>> red;
    vector<pair<int, int>> blue;
    if (s[0] == 'D') {
      assert(t[0] == 'R');
      swap(s, t);
    }
    int x = 0, y = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == 'D') {
        y++;
      } else {
        x++;
      }
      if (s[i] == 'D' && (i + 1 == s.size() || s[i + 1] == 'R')) {
        red.emplace_back(x, y);
      }
    }
    x = 0;
    y = 0;
    for (int i = 0; i < t.size(); ++i) {
      if (t[i] == 'D') {
        y++;
      } else {
        x++;
      }
      if (t[i] == 'R' && (i + 1 == t.size() || t[i + 1] == 'D')) {
        blue.emplace_back(x, y);
      }
    }
    // cerr << "red: " << endl;
    // for (auto [x, y] : red) cerr << x << " " << y << endl;
    // cerr << "blue: " << endl;
    // for (auto [x, y] : blue) cerr << x << " " << y << endl;

    sort(red.begin(), red.end());
    sort(blue.begin(), blue.end());

    constexpr int kInf = 1'000'000'000;
    vector<int> fw(H + W + 1, kInf);

    auto Update = [&](int p, int v) {
      for (int i = p + 1; i <= H + W; i += i & -i) {
        fw[i] = min(fw[i], v);
      }
    };

    auto Query = [&](int p) {
      int res = kInf;
      for (int i = p + 1; i > 0; i -= i & -i) {
        res = min(res, fw[i]);
      }
      return res;
    };

    int board = -kInf;
    for (int i = 0, j = 0; i < red.size(); ++i) {
      while (j < blue.size() && blue[j].first <= red[i].first) {
        Update(blue[j].second, blue[j].second - blue[j].first);
        j++;
      }
      int score = min(red[i].second - red[i].first, Query(red[i].second));
      board = max(board, score);
    }
    sum += board;
  }
  if (sum >= 0) {
    cout << "Second\n";
  } else {
    cout << "First\n";
  }
}
