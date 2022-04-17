#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> a(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);
  vector<set<pair<int, int>>> segs(N);

  for (int i = 0; i < N; ++i) {
    segs[i].emplace(i, i);
  }

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    if (segs[x].size() > segs[y].size()) {
      swap(x, y);
    }
    for (auto [l, r] : segs[x]) {
      auto iter = segs[y].lower_bound(make_pair(l, -1));
      if (iter != segs[y].begin() && prev(iter)->second == l - 1) {
        l = prev(iter)->first;
        segs[y].erase(prev(iter));
      }
      iter = segs[y].lower_bound(make_pair(l, -1));
      if (iter != segs[y].end() && iter->first == r + 1) {
        r = iter->second;
        segs[y].erase(iter);
      }
      segs[y].emplace(l, r);
    }
    uf[x] = y;
  };

  vector<bool> used(N);
  vector<int> ans;
  bool cont = true;

  for (int i = 0; i < N; ++i) {
    if (!cont || a[i] < 1 || a[i] > N || used[a[i] - 1] || Find(a[i] - 1) == Find(i)) {
      cont = false;
      int t = Find(i);
      auto iter = segs[t].begin();
      int x = -1;
      if (iter->first != 0) {
        x = 0;
      } else {
        x = iter->second + 1;
      }
      if (x == N) {
        assert(i == N - 1);
        for (int j = 0; j < N; ++j) {
          if (!used[j]) {
            x = j;
          }
        }
      }
      // cout << "i = " << i << " x = " << x << endl;
      used[x] = true;
      Merge(i, x);
      ans.push_back(x + 1);
    } else {
      used[a[i] - 1] = true;
      Merge(i, a[i] - 1);
      // Mark(a[i] - 1);
      ans.push_back(a[i]);
    }
  }
  for (int u : ans) {
    cout << u << " ";
  }
  cout << "\n";
  return 0;
}
