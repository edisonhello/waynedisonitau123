#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int M, N;
  cin >> M >> N;
  vector<pair<int, int>> red(M);
  vector<pair<int, int>> blue(N);
  for (int i = 0; i < M; ++i) {
    cin >> red[i].first >> red[i].second;
  }
  for (int i = 0; i < N; ++i) {
    cin >> blue[i].first >> blue[i].second;
  }

  vector<int> ds;
  for (int i = 0; i < M; ++i) {
    ds.push_back(red[i].first);
  }
  for (int i = 0; i < N; ++i) {
    ds.push_back(blue[i].first);
  }

  sort(red.begin(), red.end(), [&](const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second < rhs.second;
  });
  sort(blue.begin(), blue.end(), [&](const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second < rhs.second;
  });

  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

  auto Get = [&](const vector<pair<int, int>>& red, const vector<pair<int, int>>& blue, int mp) -> int64_t {
    // cout << "Get" << "\n" << "red: " << endl;
    // for (int i = 0; i < red.size(); ++i) cout << red[i].first << " " << red[i].second << endl;
    // cout << "blue:" << endl;
    // for (int i = 0; i < blue.size(); ++i) cout << blue[i].first << " " << blue[i].second << endl;
    if (blue.empty() || red.empty()) return 0;
    vector<pair<int, int>> r;
    for (int i = 0; i < red.size(); ++i) {
      assert(mp >= red[i].first);
      if (r.empty() || mp - red[i].first > r.back().first) {
        r.emplace_back(mp - red[i].first, red[i].second);
      }
    }
    vector<pair<int, int>> b;
    for (int i = blue.size() - 1; i >= 0; --i) {
      assert(blue[i].first >= mp);
      if (b.empty() || blue[i].first - mp > b.back().first) {
        b.emplace_back(blue[i].first - mp, blue[i].second);
      }
    }
    reverse(b.begin(), b.end());

    // cout << "r: " << endl;
    // for (int i = 0; i < r.size(); ++i) cout << r[i].first << " " << r[i].second << endl;
    // cout << "b: " << endl;
    // for (int i = 0; i < b.size(); ++i) cout << b[i].first << " " << b[i].second << endl;

    auto Area = [&](int i, int j) {
      return 1LL * (r[i].first + b[j].first) * (b[j].second - r[i].second);
    };

    auto Dfs = [&](auto dfs, int l, int r, int tl, int tr) -> int64_t {
      if (l > r) return 0;
      int m = (l + r) >> 1;
      int best = -1;
      int64_t v = -2E18;
      for (int i = tl; i <= tr; ++i) {
        int64_t w = Area(m, i);
        if (w > v) {
          v = w;
          best = i;
        }
      }
      v = max(v, dfs(dfs, l, m - 1, tl, best));
      v = max(v, dfs(dfs, m + 1, r, best, tr));
      return v;
    };

    return Dfs(Dfs, 0, r.size() - 1, 0, b.size() - 1);
  };

  auto Solve = [&](auto self, int l, int r, const vector<pair<int, int>>& red, const vector<pair<int, int>>& blue) -> int64_t {
    if (r - l == 1) {
      return 0;
    }
    int m = (l + r) >> 1;
    vector<pair<int, int>> lred, rred;
    vector<pair<int, int>> lblue, rblue;
    for (int i = 0; i < red.size(); ++i) {
      if (red[i].first < ds[m]) {
        lred.push_back(red[i]);
      } else {
        rred.push_back(red[i]);
      }
    }
    for (int i = 0; i < blue.size(); ++i) {
      if (blue[i].first < ds[m]) {
        lblue.push_back(blue[i]);
      } else {
        rblue.push_back(blue[i]);
      }
    }
    int64_t res = max(self(self, l, m, lred, lblue), self(self, m, r, rred, rblue));
    // cout << "Solve l = " << l << " r = " << r << endl;
    res = max(res, Get(lred, rblue, ds[m]));
    return res;
  };

  cout << Solve(Solve, 0, ds.size(), red, blue) << "\n";
  return 0;
}


