#include <bits/stdc++.h>
using namespace std;

int main() {
  string s; cin >> s;
  vector<int> cnt(10, 0);
  for (char c : s) ++cnt[c - '0'];

  pair<long long, long long> ans(-1, -1);

  auto Update = [&] (pair<long long, long long> p) {
    if (p.first == -1 || p.second == -1) return;
    if (ans.first == -1) ans = p;
    else ans = min(ans, min(pair<long long, long long>(p.first, p.second), pair<long long, long long>(p.second, p.first)));
  };

  auto Build = [&] (vector<int> &a) -> long long {
    int o = -1;
    for (int i = 1; i < 10; ++i) if (a[i]) { o = i; break; }
    if (o == -1) {
      if (a[0] == 0) return -1;
      else if (a[0] == 1) return 0;
      else return -1;
    }
    long long v = o;
    --a[o];
    for (int i = 0; i < 10; ++i) while (a[i]) {
      --a[i];
      if (v > 100000000000000000) return -1;
      v = v * 10 + i;
      if (v > 1000000000000000000) return -1;

    }
    return v;
  };

  auto Try = [&] (vector<int> a, vector<int> b) {
    cerr << "Try " << endl;
    long long x = Build(a);
    long long y = Build(b);
    cerr << "  x y = " << x << ' ' << y << endl;
    return make_pair(x, y);
  };

  auto Solve = [&] (vector<int> a, vector<int> b) {
    Update(Try(a, b));
    for (int i = 0; i < 10; ++i) while (b[i]) {
      --b[i];
      ++a[i];
      Update(Try(a, b));
    }
  };

  if (cnt[0]) {
    vector<int> x(10, 0);
    ++x[0];
    --cnt[0];

    Update(Try(x, cnt));
    ++cnt[0];
  }

  for (int i = 1; i < 10; ++i) if (cnt[i]) {
    vector<int> x(10, 0);
    ++x[i];
    --cnt[i];

    Solve(x, cnt);
    ++cnt[i];
    break;
  }

  if (cnt[1] >= 1 && cnt[0] >= 18) {
    vector<int> x(10, 0);
    ++x[1];
    x[0] += 18;
    --cnt[1];
    cnt[0] -= 18;

    Update(Try(x, cnt));
    ++cnt[1];
    cnt[0] += 18;
  }

  cout << ans.first << ' ' << ans.second << endl;

}
