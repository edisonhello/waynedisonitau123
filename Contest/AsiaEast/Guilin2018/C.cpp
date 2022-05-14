#include <bits/stdc++.h>
using namespace std;

pair<int, int> can_tree(int n, int m, vector<int> v) {
  sort(v.begin(), v.end());

  deque<pair<int, int>> cnt;
  
  for (int i : v) {
    if (cnt.empty() || cnt.back().first != i) cnt.emplace_back(i, 1);
    else ++cnt.back().second;
  }

  deque<pair<int, int>> can_del; // [hei, cnt]
  deque<pair<int, int>> hand; // [hei, sz]

  int add = 0;
  int last_sz = 0;

  for (auto [i, c] : cnt) {
    if (i == 1) {
      while (c--) {
        hand.emplace_back(1, 1);
      }
    } else {
      vector<int> szs;
      while (c--) {
        if (hand.size()) {
          auto [ph, sz] = hand.back();
          hand.pop_back();

          int addpt = i - 1 - ph;

          add += addpt;
          szs.push_back(sz + addpt + 1);
          can_del.emplace_back(ph, addpt + 1);
        } else {
          int addpt = i - 1;
          add += addpt;
          szs.push_back(1);
        }
      }

      for (int sz : szs) {
        hand.emplace_back(i, sz);
      }
    }

    // cout << "hand: " ;
    // for (auto [q, w] : hand) cout << "(" << q << ", " << w << ")";
    // cout << endl;
  }

  int del_cnt = 0;
  for (auto [de, sz] : hand) {
    int del = 0;
    while (can_del.size()) {
      if (can_del[0].first < de) can_del.pop_front();
      else if (can_del[0].second <= 0) can_del.pop_front();
      else {
        --can_del[0].second;
        del = 1;
        break;
      }
    }

    if (del) ++del_cnt;
  }

  int minn = add + v.size() + hand.size() - 1 - del_cnt;

  if (minn <= n) return pair{1, minn};
  return {0, minn};
}

int can_com_bin(int n, int m, vector<int> v) {
  vector<int> should_cnt(100, 0);

  for (int hi = 1; hi < 100; ++hi) {
    should_cnt[hi] = (n + 1) / 2;
    n -= should_cnt[hi];
  }

  for (int i : v) {
    if (i >= 100) return false;

    --should_cnt[i];
    if (should_cnt[i] < 0) return false;
  }
  return true;
}

#define lowbit(x) ((x) & -(x))

int is_com_bin(int n, int m, vector<int> v, int minn) {
  if (n != minn) return false;
  if (n == 4) return false;
  if (lowbit(n + 1) != n + 1) return false;

  vector<int> should_cnt(100, 0);

  int nn = n;
  for (int hi = 1; hi < 100; ++hi) {
    should_cnt[hi] = (n + 1) / 2;
    n -= should_cnt[hi];
  }
  n = nn;

  for (int i : v) {
    if (i >= 100) return false;
    --should_cnt[i];
    if (should_cnt[i] < 0) return false;
  }

  int root = __builtin_popcount(n);

  if (should_cnt[root] == 1) should_cnt[root] = 0;
  if (accumulate(should_cnt.begin(), should_cnt.end(), 0) != 0) return false;

  return true;
}

string solve() {
  int n, m;
  cin >> n >> m;
  vector<int> v(m);
  for (int i = 0; i < m; ++i) cin >> v[i];

  auto [res_can_tree, minn] = can_tree(n, m, v);
  if (!res_can_tree) return "INVALID";
  if (!can_com_bin(n, m, v)) return "IMPOSSIBLE";
  if (is_com_bin(n, m, v, minn)) return "DEFINITELY";
  return "POSSIBLE";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  for (int T = 1; T <= t; ++T) {
    string res = solve();
    cout << "Case " << T << ": " << res << endl;
  }
}

