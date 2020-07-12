#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int i, int j) { return a[i] > a[j]; });
  vector<bool> used(n);
  int64_t res = 0;
  vector<int> uf(n);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<map<int, int, greater<int>>> lr(n);
  vector<map<int, int, greater<int>>> rl(n);
  vector<int> lt(n), rg(n), mn(n);

  for (int i = 0; i < n; ++i) {
    lr[i][a[i]] = 1;
    rl[i][a[i]] = 1;
    lt[i] = a[i];
    rg[i] = a[i];
  }

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    uf[x] = y;
  };

  for (int j = 0; j < n; ++j) {
    int i = ord[j];
    if (i > 0 && used[i - 1]) {
      int f = Find(i - 1);
      map<int, int> cache;
      for (auto it = lr[f].begin(); it != lr[f].end(); ) {
        if (it->first < a[i]) break;
        cache[it->first % a[i]] += it->second;
        it = lr[f].erase(it);
      }
      for (auto it : cache) {
        lr[f][it.first] += it.second;
      }
      if (lr[f].find(0) != lr[f].end()) {
        ans += lr[f][0];
      }
    }
    if (i + 1 < n && used[i + 1]) {
      int f = Find(i + 1);
      map<int, int> cache;
      for (auto it = rl[f].begin(); it != rl[f].end(); ) {
        if (it->first < a[i]) break;
        cache[it->first % a[i]] += it->second;
        it = rl[f].erase(it);
      }
      for (auto it : cache) {
        rl[f][it.first] += it.second;
      }
      if (rl[f].find(0) != rl[f].end()) {
        ans += rl[f][0];
      }
    }
    if (i > 0 && used[i - 1] && i + 1 < n && used[i + 1]) {
      int x = Find(i - 1), y = Find(i + 1);
      if (lr[x].size() < rl[y].size()) {
        for (auto it : lr[x]) {
          if (rl[y].find(it.first) != rl[y].end()) {
            ans += 1LL * it.second * rl[y][it.first];
          }
        }
      } else {
        for (auto it : rl[y]) {
          if (lr[x].find(it.first) != lr[x].end()) {
            ans += 1LL * it.second * lr[x][it.first];
          }
        }
      }
    }
    if (i > 0 && used[i - 1]) Merge(i - 1, i);
    if (i + 1 < n && used[i + 1]) Merge(i, i + 1);
    used[i] = true;
  }
  cout << res << "\n";
  return 0;
}
