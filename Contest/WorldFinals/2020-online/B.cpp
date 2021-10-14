#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int N, M;
  cin >> N >> M;
  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  set<pair<int, int>> segs;
  vector<set<int>> vec(N);

  auto Merge = [&](int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) {
      return;
    }
    if (vec[x].size() > vec[y].size()) {
      swap(x, y);
    }
    if (vec[y].size() > 1) {
      segs.erase(make_pair(*vec[y].rbegin(), *vec[y].begin() + N));
    }
    for (int p : vec[x]) {
      auto iter = vec[y].lower_bound(p);
      if (iter != vec[y].end() && iter != vec[y].begin()) {
        segs.erase(make_pair(*prev(iter), *iter));
      }
      if (iter != vec[y].end()) {
        segs.insert(make_pair(p, *iter));
      }
      if (iter != vec[y].begin()) {
        segs.insert(make_pair(*prev(iter), p));
      }
      vec[y].insert(p);
    }
    if (vec[y].size() > 1) {
      segs.insert(make_pair(*vec[y].rbegin(), *vec[y].begin() + N));
    }
    uf[x] = y;
  };

  for (int i = 0; i < N; ++i) vec[i].insert(i);
  vector<int> nxt(N);
  for (int i = 0; i < N; ++i) nxt[i] = i;

  for (int i = 0; i < M; ++i) {
    int e, u, v;
    cin >> e >> u >> v;
    u--;
    v--;
    if (u > v) {
      swap(u, v);
    }
    if (e == 1) {
      int p = v;
      vector<int> vec;
      for (int d = 20; d >= 0; --d) {
        if (p - (1 << d) > u && nxt[p - (1 << d)] <= v) {
          p -= (1 << d);
        }
      }
      if (p - 1 > u && nxt[p - 1] > v) {
        p--;
        while (p > u && nxt[p] > v && nxt[p] < u + N) {
          vec.push_back(p);
          p--;
        }
      }
    } else {
      cout << (Find(u) == Find(v));
    }
  }
  cout << "\n";
  return 0;
}
