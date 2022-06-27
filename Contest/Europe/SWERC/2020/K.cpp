#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  int N = s.size();
  constexpr int kP[2] = {1'000'000'000 + 123, 1'000'000'000 + 87};
  constexpr int kQ[2] = {7122, 12345};
  vector<vector<int>> hs(2, vector<int>(N));
  vector<vector<int>> pw(2, vector<int>(N + 1));
  for (int i = 0; i < 2; ++i) {
    hs[i][0] = s[0];
    for (int j = 1; j < N; ++j) {
      hs[i][j] = (1LL * hs[i][j - 1] * kQ[i] + s[j]) % kP[i];
    }
    pw[i][0] = 1;
    for (int j = 1; j <= N; ++j) {
      pw[i][j] = 1LL * pw[i][j - 1] * kQ[i] % kP[i];
    }
  }

  string res = "";

  auto Query = [&](int l, int r) {
    array<int, 2> v{};
    for (int i = 0; i < 2; ++i) {
      if (l == 0) {
        v[i] = hs[i][r];
      } else {
        v[i] =
            (hs[i][r] + kP[i] - 1LL * pw[i][r - l + 1] * hs[i][l - 1] % kP[i]) %
            kP[i];
      }
    }
    return v;
  };

  auto Check = [&](int L) {
    vector<pair<array<int, 2>, int>> vec;
    for (int i = 0; i + L <= N; ++i) {
      vec.emplace_back(Query(i, i + L - 1), i);
    }
    sort(vec.begin(), vec.end());
    int f = N;
    for (int i = 0, j = 0; i < vec.size(); i = j) {
      while (j < vec.size() && vec[i].first == vec[j].first) {
        j++;
      }
      if (j - i == 1) {
        f = min(f, vec[i].second);
      }
    }
    if (f == N) {
      return false;
    }
    res = s.substr(f, L);
    return true;
  };

  int ans = N;
  for (int d = 20; d >= 0; --d) {
    if (ans - (1 << d) > 0) {
      if (Check(ans - (1 << d))) {
        ans -= (1 << d);
      }
    }
  }
  Check(ans);
  cout << res << "\n";
  return 0;
}
