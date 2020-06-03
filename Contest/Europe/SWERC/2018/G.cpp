#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  vector<int64_t> len(n);
  len[0] = s.size();
  vector<int> type(n);
  vector<vector<int64_t>> operand(n);
  for (int i = 1; i < n; ++i) {
    string p;
    cin >> p;
    if (p == "SUB") {
      int x;
      cin >> x;
      int64_t l, r;
      cin >> l >> r;
      len[i] = r - l; 
      type[i] = 0;
      operand[i] = {x, l, r};
    } else {
      int x, y;
      cin >> x >> y;
      len[i] = len[x] + len[y];
      type[i] = 1;
      operand[i] = {x, y};
    }
  }
  vector<vector<pair<int64_t, int>>> cut(n);
  for (int i = n - 1; i >= 0; --i) {
    cut[i].emplace_back(0, 0);
    cut[i].emplace_back(len[i], 0);
    sort(cut[i].begin(), cut[i].end());
    cut[i].resize(unique(cut[i].begin(), cut[i].end()) - cut[i].begin());
    if (i == 0) break;
    if (type[i] == 0) {
      int x = operand[i][0];
      int64_t l = operand[i][1];
      int64_t r = operand[i][2];
      cut[x].emplace_back(l, 0);
      cut[x].emplace_back(r, 0);
      for (auto j : cut[i]) {
        cut[x].emplace_back(j.first + l, 0);
      }
    } else {
      int x = operand[i][0];
      int y = operand[i][1];
      for (auto j : cut[i]) {
        if (j.first <= len[x]) {
          cut[x].emplace_back(j.first, 0);
        } else {
          cut[y].emplace_back(j.first - len[x], 0);
        }
      }
    }
  }
  constexpr int kMod = 1'000'000'000 + 7;
  // vector<map<pair<int64_t, int64_t>, int>> seg(n);
  for (auto it = cut[0].begin(); next(it) != cut[0].end(); it++) {
    int sum = 0;
    for (int k = it->first; k < next(it)->first; ++k) {
      (sum += s[k]) %= kMod;
    }
    it->second = sum;
  }
  for (int i = 1; i < n; ++i) {
    if (type[i] == 0) {
      int x = operand[i][0];
      int64_t tl = operand[i][1];
      int64_t tr = operand[i][2];
      for (auto kit = cut[i].begin(); next(kit) != cut[i].end(); kit++) {
        int64_t l = kit->first, r = next(kit)->first - 1;
        auto it = lower_bound(cut[x].begin(), cut[x].end(), make_pair(l + tl, -1));
        assert(it != cut[x].end() && it->first == l + tl);
        assert(next(it) != cut[x].end());
        int sum = 0;
        while (next(it) != cut[x].end()) {
          (sum += it->second) %= kMod;
          if (next(it)->first - 1 == r + tl) break;
          it++;
        }
        kit->second = sum;
      }
    } else {
      int x = operand[i][0];
      int y = operand[i][1];
      for (auto kit = cut[i].begin(); next(kit) != cut[i].end(); kit++) {
        int64_t l = kit->first, r = next(kit)->first - 1;
        int sum = 0;
        if (l < len[x]) {
          auto it = lower_bound(cut[x].begin(), cut[x].end(), make_pair(l, -1));
          assert(it != cut[x].end() && it->first == l);
          assert(next(it) != cut[x].end());
          if (r < len[x]) {
            while (next(it) != cut[x].end()) {
              (sum += it->second) %= kMod;
              if (next(it)->first - 1 == r) break;
              it++;
            }
          } else {
            while (next(it) != cut[x].end()) {
              (sum += it->second) %= kMod;
              it++;
            }
            it = cut[y].begin();
            while (next(it) != cut[y].end()) {
              (sum += it->second) %= kMod;
              if (next(it)->first - 1 == r - len[x]) break;
              it++;
            }
          }
        } else {
          auto it = lower_bound(cut[y].begin(), cut[y].end(), make_pair(l - len[x], -1));
          assert(it != cut[y].end() && it->first == l - len[x]);
          assert(next(it) != cut[y].end());
          while (next(it) != cut[y].end()) {
            (sum += it->second) %= kMod;
            if (next(it)->first - 1 == (r - len[x])) break;
            it++;
          }
        }
        kit->second = sum;
      }
    }
  }
  int res = 0;
  for (auto it : cut[n - 1]) (res += it.second) %= kMod;
  cout << res << "\n";
  return 0;
}
